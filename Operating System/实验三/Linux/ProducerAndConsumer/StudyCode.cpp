#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define NEED_P 2
#define NEED_C 3
#define WORKS_P 6
#define WORKS_C 4

#define BUF_LENGTH (sizeof(struct mybuffer))
#define LETTER_NUM 3
#define SHM_MODE 0600

#define SEM_ALL_KEY 1234
#define SEM_EMPTY 0
#define SEM_FULL 1

//缓冲区结构（循环队列）
struct mybuffer
{
    char letter[LETTER_NUM];
    int head;
    int tail;
    int is_empty;
};

//得到5以内的一个随机数
int get_random()
{
    int t;
    srand((unsigned)(getpid() + time(NULL)));
    t = rand() % 5;
    return t;
}

//得到A~Z的一个随机字母
char get_letter()
{
    char a;
    srand((unsigned)(getpid() + time(NULL)));
    a = (char)((char)(rand() % 26) + 'A');
    return a;
}

//P操作
void p(int sem_id, int sem_num)
{
    struct sembuf xx;
    xx.sem_num = sem_num;
    xx.sem_op = -1;
    xx.sem_flg = 0;
    semop(sem_id, &xx, 1);
}

//V操作
void v(int sem_id, int sem_num)
{
    struct sembuf xx;
    xx.sem_num = sem_num;
    xx.sem_op = 1;
    xx.sem_flg = 0;
    semop(sem_id, &xx, 1);
}

//主函数
int main(int argc, char * argv[])
{
    int i, j;
    int shm_id, sem_id;
    int num_p = 0, num_c = 0;
    struct mybuffer * shmptr;
    char lt;
    time_t now;
    pid_t pid_p, pid_c;
    
    sem_id = semget(SEM_ALL_KEY, 2, IPC_CREAT | 0660);
    if (sem_id >= 0)
    {
        printf("Main process starts. Semaphore created.\n");
    }
    semctl(sem_id, SEM_EMPTY, SETVAL, LETTER_NUM);
    semctl(sem_id, SEM_FULL, SETVAL, 0);
    
    if ((shm_id = shmget(IPC_PRIVATE, BUF_LENGTH, SHM_MODE)) < 0)
    {
        printf("Error on shmget.\n");
        exit(1);
    }
    if ((shmptr = shmat(shm_id, 0, 0)) == (void *)-1)
    {
        printf("Error on shmat.\n");
        exit(1);
    }
    shmptr->head = 0;
    shmptr->tail = 0;
    shmptr->is_empty = 1;
    
    while ((num_p++) < NEED_P)
    {
        if ((pid_p = fork()) < 0)
        {
            printf("Error on fork.\n");
            exit(1);
        }
        //如果是子进程，开始创建生产者
        if (pid_p == 0)
        {
            if ((shmptr = shmat(shm_id, 0, 0)) == (void *)-1)
            {
                printf("Error on shmat.\n");
                exit(1);
            }
            for (i = 0; i < WORKS_P; i++)
            {
                p(sem_id, SEM_EMPTY);
                sleep(get_random());
                shmptr->letter[shmptr->tail] = lt = get_letter();
                shmptr->tail = (shmptr->tail + 1) % LETTER_NUM;
                shmptr->is_empty = 0;
                now = time(NULL);
                printf("%02d:%02d:%02d\t", localtime(&now)->tm_hour, localtime(&now)->tm_min, localtime(&now)->tm_sec);
                for (j = (shmptr->tail - 1 >= shmptr->head) ? (shmptr->tail - 1) : (shmptr->tail - 1 + LETTER_NUM); !(shmptr->is_empty) && j >= shmptr->head; j--)
                {
                    printf("%c", shmptr->letter[j % LETTER_NUM]);
                }
                printf("\tProducer %d puts '%c'.\n", num_p, lt);
                fflush(stdout);
                v(sem_id, SEM_FULL);
            }
            shmdt(shmptr);
            exit(0);
        }
    }

    while (num_c++ < NEED_C)
    {
        if ((pid_c = fork()) < 0)
        {
            printf("Error on fork.\n");
            exit(1);
        }
        //如果是子进程，开始创建消费者
        if (pid_c == 0)
        {
            if ((shmptr = shmat(shm_id, 0, 0)) == (void *)-1)
            {
                printf("Error on shmat.\n");
                exit(1);
            }
            for (i = 0; i < WORKS_C; i++)
            {
                p(sem_id, SEM_FULL);
                sleep(get_random());
                lt = shmptr->letter[shmptr->head];
                shmptr->head = (shmptr->head + 1) % LETTER_NUM;
                shmptr->is_empty = (shmptr->head == shmptr->tail);
                now = time(NULL);
                printf("%02d:%02d:%02d\t", localtime(&now)->tm_hour, localtime(&now)->tm_min, localtime(&now)->tm_sec);
                for (j = (shmptr->tail - 1 >= shmptr->head) ? (shmptr->tail - 1) : (shmptr->tail - 1 + LETTER_NUM); !(shmptr->is_empty) && j >= shmptr->head; j--)
                {
                    printf("%c", shmptr->letter[j % LETTER_NUM]);
                }
                printf("\tConsumer %d gets '%c'.\n", num_c, lt);
                fflush(stdout);
                v(sem_id, SEM_EMPTY);
            }
            shmdt(shmptr);
            exit(0);
        }
    }
    
    //主控程序最后退出
    while(wait(0) != -1);
    shmdt(shmptr);
    shmctl(shm_id, IPC_RMID, 0);
    semctl(sem_id, IPC_RMID, 0);
    printf("Main process ends.\n");
    fflush(stdout);
    exit(0);
}
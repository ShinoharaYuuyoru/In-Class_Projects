#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

//#define ID_MAIN 0
//#define ID_PRODUCER_START 1
//#define ID_PRODUCER_ENDS 3
//#define ID_CONSUMER_START 4
//#define ID_CONSUMER_ENDS 7
#define ID_PRODUCER_NEED 3
#define ID_CONSUMER_NEED 4

#define PRODUCER_WORKS_TIMES 4
#define CONSUMER_WORKS_TIMES 3

#define BUFFER_SIZE 4
//#define PROCESS_NUM 7
#define SHM_MODE 0600

#define SEM_EMPTY 0
#define SEM_FULL 1
#define SEM_MUTEX 2

/*The Buffer, use to catch.*/
struct myBuffer
{
	int index;
	char Buffer[BUFFER_SIZE + 1];
	int head;
	int tail;
	int isEmpty;
};

void op_P(int sem_id, int sem_num);
void op_V(int sem_id, int sem_num);
int getRandomInt();
char getRandomLetter();

int main(int argc, char * argv[])
{
	time_t nowTime;
	pid_t pid_Producer, pid_Consumer;

	int SEM_ALL_KEY = ftok("/tmp", 0x66);
	if (SEM_ALL_KEY < 0)
	{
		printf("ftok SEM_ALL_KEY Error!\n");

		return -1;
	}
	int SEM_ID = semget(SEM_ALL_KEY, 3, IPC_CREAT | 0600);
	if (SEM_ID >= 0)
	{
		printf("Main process starts.\n");
	}
	else
	{
		printf("Semaphore Create Error!\n");

		return -1;
	}
	semctl(SEM_ID, SEM_EMPTY, SETVAL, BUFFER_SIZE);
	semctl(SEM_ID, SEM_FULL, SETVAL, 0);
	semctl(SEM_ID, SEM_MUTEX, SETVAL, 1);

	int SHM_ID = shmget(IPC_PRIVATE, sizeof(struct myBuffer), SHM_MODE);
	if (SHM_ID < 0)
	{
		printf("SharedMemory Create Error!\n");

		return -1;
	}

	struct myBuffer *SHMPTR;
	SHMPTR = (struct myBuffer *)shmat(SHM_ID, 0, 0);
	if (SHMPTR == (void *)-1)
	{
		printf("shmat Error!\n");

		return -1;
	}
	SHMPTR->index = 0;
	SHMPTR->head = 0;
	SHMPTR->tail = 0;
	SHMPTR->isEmpty = 1;
	int i;
	for (i = 0;i<BUFFER_SIZE;i++)
	{
		SHMPTR->Buffer[i] = '-';
	}
	SHMPTR->Buffer[BUFFER_SIZE] = '\0';

	/*The Producer Process.*/
	int producerNum;
	for (producerNum = 0;producerNum < ID_PRODUCER_NEED; producerNum++)
	{
		pid_Producer = fork();
		if (pid_Producer<0)
		{
			printf("fork Error!\n");

			return -1;
		}

		if (pid_Producer == 0)
		{
			SHMPTR = (struct myBuffer *)shmat(SHM_ID, 0, 0);
			if (SHMPTR == (void *)-1)
			{
				printf("shmat Error!\n");

				return -1;
			}

			/*Start Producer Work Times.*/
			srand((unsigned)(getpid() + time(NULL)));
			char productLetter;
			int i;
			for (i = 0;i<PRODUCER_WORKS_TIMES;i++)
			{
				usleep(getRandomInt());
				op_P(SEM_ID, SEM_EMPTY);
				op_P(SEM_ID, SEM_MUTEX);

				/*Produce*/
				productLetter = getRandomLetter();
				SHMPTR->Buffer[SHMPTR->tail] = productLetter;
				SHMPTR->tail = (SHMPTR->tail + 1) % BUFFER_SIZE;
				SHMPTR->isEmpty = 0;
				SHMPTR->index++;

				/*Print the index, time, and the product.*/
				nowTime = time(NULL);
				printf("[%02d]\t", SHMPTR->index);	//Print index.
				printf("%02d:%02d:%02d\t", localtime(&nowTime)->tm_hour, localtime(&nowTime)->tm_min, localtime(&nowTime)->tm_sec);	//Print now time.
				int j;
				for (j = 0; j<BUFFER_SIZE; j++)
				{
					printf("%c", SHMPTR->Buffer[j]);
				}
				printf("\tProducer No.%d produced '%c'.\n", producerNum + 1, productLetter);
				
				op_V(SEM_ID, SEM_FULL);
				op_V(SEM_ID, SEM_MUTEX);
			}
			shmdt(SHMPTR);
			printf("Producer No.%d ends.\n", producerNum + 1);

			return 0;
		}
	}

	/*The Consumer Process.*/
	int consumerNum;
	for (consumerNum = 0;consumerNum < ID_CONSUMER_NEED; consumerNum++)
	{
		pid_Consumer = fork();
		if (pid_Consumer<0)
		{
			printf("fork Error!\n");

			return -1;
		}

		if (pid_Consumer == 0)
		{
			SHMPTR = (struct myBuffer *)shmat(SHM_ID, 0, 0);
			if (SHMPTR == (void *)-1)
			{
				printf("shmat Error!\n");

				return -1;
			}

			/*Start Consumer Work Times.*/
			srand((unsigned)(getpid() + time(NULL)));
			char consumptionLetter;
			int i;
			for (i = 0;i<CONSUMER_WORKS_TIMES;i++)
			{
				usleep(getRandomInt());
				op_P(SEM_ID, SEM_FULL);
				op_P(SEM_ID, SEM_MUTEX);

				/*Consume*/
				consumptionLetter = SHMPTR->Buffer[SHMPTR->head];
				SHMPTR->Buffer[SHMPTR->head] = '-';
				SHMPTR->head = (SHMPTR->head + 1) % BUFFER_SIZE;
				SHMPTR->isEmpty = (SHMPTR->head == SHMPTR->tail);
				SHMPTR->index++;

				/*Print the index, time, and the product.*/
				nowTime = time(NULL);
				printf("[%02d]\t", SHMPTR->index);	//Print index.
				printf("%02d:%02d:%02d\t", localtime(&nowTime)->tm_hour, localtime(&nowTime)->tm_min, localtime(&nowTime)->tm_sec);	//Print now time.
				int j;
				for (j = 0; j<BUFFER_SIZE; j++)
				{
					printf("%c", SHMPTR->Buffer[j]);
				}
				printf("\tConsumer No.%d consumed '%c'.\n", consumerNum + 1, consumptionLetter);
				
				op_V(SEM_ID, SEM_EMPTY);
				op_V(SEM_ID, SEM_MUTEX);
			}
			shmdt(SHMPTR);
			printf("Consumer No.%d ends.\n", consumerNum + 1);

			return 0;
		}
	}

	/*Main process ends.*/
	while (wait(NULL) != -1);
	shmdt(SHMPTR);
	shmctl(SHM_ID, IPC_RMID, 0);
	shmctl(SEM_ID, IPC_RMID, 0);
	printf("Main Process ends.\n");
	fflush(stdout);

	return 0;
}

/*P operation*/
void op_P(int sem_id, int sem_num)
{
	struct sembuf TMP;
	TMP.sem_num = sem_num;
	TMP.sem_op = -1;
	TMP.sem_flg = 0;
	semop(sem_id, &TMP, 1);
}

/*V operation*/
void op_V(int sem_id, int sem_num)
{
	struct sembuf TMP;
	TMP.sem_num = sem_num;
	TMP.sem_op = 1;
	TMP.sem_flg = 0;
	semop(sem_id, &TMP, 1);
}

/*Get the number between 0 - 3000000, used to stop between 0 - 3 seconds.*/
int getRandomInt()
{
	int randnum;
	//srand((unsigned)(getpid() + time(NULL)));
	randnum = rand() % 3000001;

	return randnum;
}

/*Get the Letter P or Q or Y, is the product.*/
char getRandomLetter()
{
	char letterMap[4] = { 'P','Q','Y','\0' };
	int randNum;
	//srand((unsigned)(getpid() + time(NULL)));
	randNum = rand() % 3;

	return letterMap[randNum];
}

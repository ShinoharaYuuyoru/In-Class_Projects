#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#define ID_M 0
#define ID_P_FROM 1
#define ID_P_TO 2
#define ID_C_FROM 3
#define ID_C_TO 5
#define PROCESS_NUM 5
#define WORKS_P 6
#define WORKS_C 4

#define LETTER_NUM 3
#define SHM_NAME "BUFFER"

//缓冲区结构（循环队列）
struct mybuffer
{
	char letter[LETTER_NUM];
	int head;
	int tail;
	int is_empty;
};

//共享主存区结构
struct sharemem
{
	struct mybuffer data;
	int index;
	HANDLE semEmpty;
	HANDLE semFull;
};

//文件映射对象句柄
static HANDLE hMapping;

//子进程句柄数组
static HANDLE hs[PROCESS_NUM + 1];

//得到5000以内的一个随机数
int get_random()
{
	int t;
	srand((unsigned)(GetCurrentProcessId() + time(NULL)));
	t = rand() % 5000;
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

//进程克隆（通过参数传递进程的序列号）
void StartClone(int nCloneID)
{
	char szFilename[MAX_PATH];
	char szCmdLine[MAX_PATH];
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	GetModuleFileName(NULL, szFilename, MAX_PATH);
	sprintf(szCmdLine, "\"%s\" %d", szFilename, nCloneID);
	memset(&si, 0, sizeof(si));
	si.cb = sizeof(si);
	//创建子进程
	BOOL bCreateOK = CreateProcess(szFilename, szCmdLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
	hs[nCloneID] = pi.hProcess;
	return;
}

//创建共享主存区
HANDLE MakeSharedFile()
{
	//创建文件映射对象
	HANDLE hMapping = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(struct sharemem), SHM_NAME);
	if (hMapping != INVALID_HANDLE_VALUE)
	{
		//在文件映射上创建视图
		LPVOID pData = MapViewOfFile(hMapping, FILE_MAP_ALL_ACCESS, 0, 0, 0);
		if (pData != NULL)
		{
			ZeroMemory(pData, sizeof(struct sharemem));
		}
		//关闭文件视图
		UnmapViewOfFile(pData);
	}
	return (hMapping);
}

//主函数
int main(int argc, char * argv[])
{
	int i, j, k;
	int pindex = 1; //下一个要创建的子进程的序列号
	int nClone = ID_M; //本进程序列号
	char lt;
	SYSTEMTIME systime;

	//如果有参数，就作为子进程的序列号
	if (argc > 1)
	{
		sscanf(argv[1], "%d", &nClone);
	}

	//对于所有进程
	printf("Process ID: %d , Serial No: %d\n", GetCurrentProcessId(), nClone);

	//对于主控进程
	if (nClone == ID_M)
	{
		printf("Main process starts.\n");
		//创建数据文件
		hMapping = MakeSharedFile();
		//映射视图
		HANDLE hFileMapping = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, SHM_NAME);
		LPVOID pFile = MapViewOfFile(hFileMapping, FILE_MAP_ALL_ACCESS, 0, 0, 0);
		if (pFile != NULL)
		{
			struct sharemem * shm = (struct sharemem *)(pFile);
			shm->data.head = 0;
			shm->data.tail = 0;
			shm->index = 0;
			shm->semEmpty = CreateSemaphore(NULL, LETTER_NUM, LETTER_NUM, "SEM_EMPTY");
			shm->semFull = CreateSemaphore(NULL, 0, LETTER_NUM, "SEM_FULL");
			UnmapViewOfFile(pFile);
			pFile = NULL;
		}
		else
		{
			printf("Error on OpenFileMapping.\n");
		}
		CloseHandle(hFileMapping);

		//依次创建子进程
		while (pindex <= PROCESS_NUM)
		{
			StartClone(pindex++);
		}
		//等待子进程完成
		for (k = 1; k < PROCESS_NUM + 1; k++)
		{
			WaitForSingleObject(hs[k], INFINITE);
			CloseHandle(hs[k]);
		}
		printf("Main process ends.\n");
	}
	//对于生产者进程
	else if (nClone >= ID_P_FROM && nClone <= ID_P_TO)
	{
		printf("Producer %d process starts.\n", nClone - ID_M);
		//映射视图
		HANDLE hFileMapping = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, SHM_NAME);
		LPVOID pFile = MapViewOfFile(hFileMapping, FILE_MAP_ALL_ACCESS, 0, 0, 0);
		if (pFile != NULL)
		{
			struct sharemem * shm = (struct sharemem *)(pFile);
			shm->semEmpty = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "SEM_EMPTY");
			shm->semFull = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "SEM_FULL");
			for (i = 0; i < WORKS_P; i++)
			{
				WaitForSingleObject(shm->semEmpty, INFINITE);
				sleep(get_random());
				shm->index++;
				shm->data.letter[shm->data.tail] = lt = get_letter();
				shm->data.tail = (shm->data.tail + 1) % LETTER_NUM;
				shm->data.is_empty = 0;
				GetLocalTime(&systime);
				printf("[%02d]\t", shm->index);
				printf("%02d:%02d:%02d\t", systime.wHour, systime.wMinute, systime.wSecond);
				for (j = (shm->data.tail - 1 >= shm->data.head) ? (shm->data.tail - 1) : (shm->data.tail - 1 + LETTER_NUM); !(shm->data.is_empty) && j >= shm->data.head; j--)
				{
					printf("%c", shm->data.letter[j % LETTER_NUM]);
				}
				printf("\tProducer %d puts '%c'.\n", nClone - ID_M, lt);
				ReleaseSemaphore(shm->semFull, 1, NULL);
			}
			UnmapViewOfFile(pFile);
			pFile = NULL;
		}
		else
		{
			printf("Error on OpenFileMapping.\n");
		}
		CloseHandle(hFileMapping);
		printf("Producer %d process ends.\n", nClone - ID_M);
	}
	//对于消费者进程
	else if (nClone >= ID_C_FROM && nClone <= ID_C_TO)
	{
		printf("Consumer %d process starts.\n", nClone - ID_P_TO);
		//映射视图
		HANDLE hFileMapping = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, SHM_NAME);
		LPVOID pFile = MapViewOfFile(hFileMapping, FILE_MAP_ALL_ACCESS, 0, 0, 0);
		if (pFile != NULL)
		{
			struct sharemem * shm = (struct sharemem *)(pFile);
			shm->semEmpty = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "SEM_EMPTY");
			shm->semFull = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "SEM_FULL");
			for (i = 0; i < WORKS_C; i++)
			{
				WaitForSingleObject(shm->semFull, INFINITE);
				sleep(get_random());
				shm->index++;
				lt = shm->data.letter[shm->data.head];
				shm->data.head = (shm->data.head + 1) % LETTER_NUM;
				shm->data.is_empty = (shm->data.head == shm->data.tail);
				GetLocalTime(&systime);
				printf("[%02d]\t", shm->index);
				printf("%02d:%02d:%02d\t", systime.wHour, systime.wMinute, systime.wSecond);
				for (j = (shm->data.tail - 1 >= shm->data.head) ? (shm->data.tail - 1) : (shm->data.tail - 1 + LETTER_NUM); !(shm->data.is_empty) && j >= shm->data.head; j--)
				{
					printf("%c", shm->data.letter[j % LETTER_NUM]);
				}
				printf("\tConsumer %d gets '%c'.\n", nClone - ID_P_TO, lt);
				ReleaseSemaphore(shm->semEmpty, 1, NULL);
			}
			UnmapViewOfFile(pFile);
			pFile = NULL;
		}
		else
		{
			printf("Error on OpenFileMapping.\n");
		}
		CloseHandle(hFileMapping);
		printf("Consumer %d process ends.\n", nClone - ID_P_TO);
	}

	CloseHandle(hMapping);
	hMapping = INVALID_HANDLE_VALUE;
	return 0;
}
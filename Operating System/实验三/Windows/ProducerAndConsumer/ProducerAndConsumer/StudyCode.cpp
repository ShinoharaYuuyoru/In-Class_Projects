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

//�������ṹ��ѭ�����У�
struct mybuffer
{
	char letter[LETTER_NUM];
	int head;
	int tail;
	int is_empty;
};

//�����������ṹ
struct sharemem
{
	struct mybuffer data;
	int index;
	HANDLE semEmpty;
	HANDLE semFull;
};

//�ļ�ӳ�������
static HANDLE hMapping;

//�ӽ��̾������
static HANDLE hs[PROCESS_NUM + 1];

//�õ�5000���ڵ�һ�������
int get_random()
{
	int t;
	srand((unsigned)(GetCurrentProcessId() + time(NULL)));
	t = rand() % 5000;
	return t;
}

//�õ�A~Z��һ�������ĸ
char get_letter()
{
	char a;
	srand((unsigned)(getpid() + time(NULL)));
	a = (char)((char)(rand() % 26) + 'A');
	return a;
}

//���̿�¡��ͨ���������ݽ��̵����кţ�
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
	//�����ӽ���
	BOOL bCreateOK = CreateProcess(szFilename, szCmdLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
	hs[nCloneID] = pi.hProcess;
	return;
}

//��������������
HANDLE MakeSharedFile()
{
	//�����ļ�ӳ�����
	HANDLE hMapping = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(struct sharemem), SHM_NAME);
	if (hMapping != INVALID_HANDLE_VALUE)
	{
		//���ļ�ӳ���ϴ�����ͼ
		LPVOID pData = MapViewOfFile(hMapping, FILE_MAP_ALL_ACCESS, 0, 0, 0);
		if (pData != NULL)
		{
			ZeroMemory(pData, sizeof(struct sharemem));
		}
		//�ر��ļ���ͼ
		UnmapViewOfFile(pData);
	}
	return (hMapping);
}

//������
int main(int argc, char * argv[])
{
	int i, j, k;
	int pindex = 1; //��һ��Ҫ�������ӽ��̵����к�
	int nClone = ID_M; //���������к�
	char lt;
	SYSTEMTIME systime;

	//����в���������Ϊ�ӽ��̵����к�
	if (argc > 1)
	{
		sscanf(argv[1], "%d", &nClone);
	}

	//�������н���
	printf("Process ID: %d , Serial No: %d\n", GetCurrentProcessId(), nClone);

	//�������ؽ���
	if (nClone == ID_M)
	{
		printf("Main process starts.\n");
		//���������ļ�
		hMapping = MakeSharedFile();
		//ӳ����ͼ
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

		//���δ����ӽ���
		while (pindex <= PROCESS_NUM)
		{
			StartClone(pindex++);
		}
		//�ȴ��ӽ������
		for (k = 1; k < PROCESS_NUM + 1; k++)
		{
			WaitForSingleObject(hs[k], INFINITE);
			CloseHandle(hs[k]);
		}
		printf("Main process ends.\n");
	}
	//���������߽���
	else if (nClone >= ID_P_FROM && nClone <= ID_P_TO)
	{
		printf("Producer %d process starts.\n", nClone - ID_M);
		//ӳ����ͼ
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
	//���������߽���
	else if (nClone >= ID_C_FROM && nClone <= ID_C_TO)
	{
		printf("Consumer %d process starts.\n", nClone - ID_P_TO);
		//ӳ����ͼ
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
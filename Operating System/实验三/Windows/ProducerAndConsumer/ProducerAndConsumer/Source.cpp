#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <tchar.h>

#define ID_MAIN 0
#define ID_PRODUCER_START 1
#define ID_PRODUCER_ENDS 3
#define ID_CONSUMER_START 4
#define ID_CONSUMER_ENDS 7

#define PRODUCER_WORKS_TIMES 4
#define CONSUMER_WORKS_TIMES 3

#define BUFFER_SIZE 4
#define PROCESS_NUM 7
TCHAR sharedMemName[] = TEXT("Global\\MyFileMappingObject");

/*The Buffer, use to cache.*/
struct myBuffer
{
	char Buffer[BUFFER_SIZE + 1];
	int head;
	int tail;
	int isEmpty;
};

/*The sharedMemory used to realize Buffer.*/
struct sharedMem
{
	struct myBuffer bufferData;
	int index;
};

/*File Mapping HANDLE.*/
static HANDLE hMapping;

/*The HANDLE array of Child Process.*/
static HANDLE hChildProcess[PROCESS_NUM + 1];

int getRandomInt();
char getRandomLetter();
HANDLE MakeSharedMem();
void cloneChildProcess(int nCloneID);
void TCHAR_to_char(const TCHAR * tchar, char * _char);
void char_to_TCHAR(const char * _char, TCHAR * tchar);

int main(int argc, char *argv[])
{
	int nClone = ID_MAIN;
	SYSTEMTIME nowTime;
	HANDLE semEmpty;
	HANDLE semFull;
	HANDLE semMutex;

	/*Give the  parameter to nClone.*/
	if (argc > 1)
	{
		sscanf(argv[1], "%d", &nClone);
	}

	/*Print Process ID and Serial Number.*/
	printf("Process ID: %d, Serial No: %d.\n", GetCurrentProcessId(), nClone);

	if (nClone == ID_MAIN)
	{
		printf("Main Process starts.\n");

		/*Start the shared memory.*/
		hMapping = MakeSharedMem();
		/*Mapping the view*/
		HANDLE hFileMapping = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, sharedMemName);
		LPVOID pFile = MapViewOfFile(hFileMapping, FILE_MAP_ALL_ACCESS, 0, 0, 0);
		if (pFile == NULL)
		{
			printf("OpenFileMapping Error!\n");

			return -1;
		}
		else
		{
			struct sharedMem * SHM = (struct sharedMem *)pFile;
			memset(SHM->bufferData.Buffer, '-', sizeof(SHM->bufferData.Buffer));
			SHM->bufferData.Buffer[BUFFER_SIZE] = '\0';
			SHM->bufferData.head = 0;
			SHM->bufferData.tail = 0;
			SHM->index = 0;
			semEmpty = CreateSemaphore(NULL, BUFFER_SIZE, BUFFER_SIZE, TEXT("SEM_EMPTY"));
			semFull = CreateSemaphore(NULL, 0, BUFFER_SIZE, TEXT("SEM_FULL"));
			semMutex = CreateMutex(NULL, FALSE, TEXT("SEM_MUTEX"));
			UnmapViewOfFile(pFile);
			pFile = NULL;
		}
		CloseHandle(hFileMapping);

		/*Clone the Child Process.*/
		int childprocessNum = 1;
		for (childprocessNum = 1;childprocessNum <= PROCESS_NUM;childprocessNum++)
		{
			cloneChildProcess(childprocessNum);
		}

		/*Wait child process ends.*/
		int i;
		for (i = 1; i <= PROCESS_NUM;i++)
		{
			WaitForSingleObject(hChildProcess[i], INFINITE);
			CloseHandle(hChildProcess[i]);
		}
		printf("Main Process ends.\n");
	}
	else
	{
		/*The Producer Process.*/
		if (nClone >= ID_PRODUCER_START&&nClone <= ID_PRODUCER_ENDS)
		{
			printf("Producer No.%d starts.\n", nClone - ID_MAIN);

			/*Mapping the view.*/
			HANDLE hFileMapping = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, sharedMemName);
			LPVOID pFile = MapViewOfFile(hFileMapping, FILE_MAP_ALL_ACCESS, 0, 0, 0);
			if (pFile == NULL)
			{
				printf("OpenFileMapping Error!\n");

				return -1;
			}
			else
			{
				struct sharedMem * SHM = (struct sharedMem*)pFile;
				semEmpty = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, TEXT("SEM_EMPTY"));
				semFull = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, TEXT("SEM_FULL"));
				semMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, TEXT("SEM_MUTEX"));

				/*Start Producer Work Times.*/
				srand((unsigned)(GetCurrentProcessId() + time(NULL)));
				char productLetter;
				int i;
				for (i = 0;i < PRODUCER_WORKS_TIMES;i++)
				{
					Sleep(getRandomInt());
					WaitForSingleObject(semEmpty, INFINITE);
					WaitForSingleObject(semMutex, INFINITE);

					/*Produce*/
					productLetter = getRandomLetter();
					SHM->index++;
					SHM->bufferData.Buffer[SHM->bufferData.tail] = productLetter;
					SHM->bufferData.tail = (SHM->bufferData.tail + 1) % BUFFER_SIZE;
					SHM->bufferData.isEmpty = 0;

					/*Print the index, time, and the product.*/
					GetLocalTime(&nowTime);
					printf("[%02d]\t", SHM->index);	//Print index.
					printf("%02d:%02d:%02d\t", nowTime.wHour, nowTime.wMinute, nowTime.wSecond);	//Print now time.
					int j;
					for (j = 0;j < BUFFER_SIZE;j++)
					{
						printf("%c", SHM->bufferData.Buffer[j]);
					}
					printf("\tProducer No.%d produced '%c'.\n", nClone - ID_MAIN, productLetter);

					ReleaseSemaphore(semFull, 1, NULL);
					ReleaseMutex(semMutex);
				}
				UnmapViewOfFile(pFile);
				pFile = NULL;
			}
			CloseHandle(hFileMapping);
			printf("Producer No.%d ends.\n", nClone - ID_MAIN);
		}
		else
		{
			/*The Consumer Process.*/
			if (nClone >= ID_CONSUMER_START&&nClone <= ID_CONSUMER_ENDS)
			{
				printf("Consumer No.%d starts.\n", nClone - ID_PRODUCER_ENDS);

				/*Mapping the view.*/
				HANDLE hFileMapping = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, sharedMemName);
				LPVOID pFile = MapViewOfFile(hFileMapping, FILE_MAP_ALL_ACCESS, 0, 0, 0);
				if (pFile == NULL)
				{
					printf("OpenFileMapping Error!\n");

					return -1;
				}
				else
				{
					struct sharedMem * SHM = (struct sharedMem*)pFile;
					semEmpty = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, TEXT("SEM_EMPTY"));
					semFull = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, TEXT("SEM_FULL"));
					semMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, TEXT("SEM_MUTEX"));

					/*Start Consumer Work Times.*/
					srand((unsigned)(GetCurrentProcessId() + time(NULL)));
					char ConsumptionLetter;
					int i;
					for (i = 0; i < CONSUMER_WORKS_TIMES;i++)
					{
						Sleep(getRandomInt());
						WaitForSingleObject(semFull, INFINITE);
						WaitForSingleObject(semMutex, INFINITE);

						/*Consume*/
						SHM->index++;
						ConsumptionLetter = SHM->bufferData.Buffer[SHM->bufferData.head];
						SHM->bufferData.Buffer[SHM->bufferData.head] = '-';	//Set Used!
						SHM->bufferData.head = (SHM->bufferData.head + 1) % BUFFER_SIZE;
						SHM->bufferData.isEmpty = (SHM->bufferData.head == SHM->bufferData.tail);

						/*Print the index, time, and the consumption.*/
						GetLocalTime(&nowTime);
						printf("[%02d]\t", SHM->index);
						printf("%02d:%02d:%02d\t", nowTime.wHour, nowTime.wMinute, nowTime.wSecond);
						int j;
						for (j = 0;j < BUFFER_SIZE;j++)
						{
							printf("%c", SHM->bufferData.Buffer[j]);
						}
						printf("\tConsumer No.%d consumed '%c'.\n", nClone - ID_PRODUCER_ENDS, ConsumptionLetter);

						ReleaseSemaphore(semEmpty, 1, NULL);
						ReleaseMutex(semMutex);
					}
					UnmapViewOfFile(pFile);
					pFile == NULL;
				}
				CloseHandle(hFileMapping);
				printf("Consumer No.%d ends.\n", nClone - ID_PRODUCER_ENDS);
			}
			else
			{
				printf("nClone Error!\n");
				
				return -1;
			}
		}
	}

	CloseHandle(hMapping);
	hMapping == INVALID_HANDLE_VALUE;

	return 0;
}

/*Get the number between 0 - 3000, used to stop between 0 - 3 seconds.*/
int getRandomInt()
{
	int randnum;
	//srand((unsigned)(GetCurrentProcessId() + time(NULL)));
	randnum = rand() % 3001;
	
	return randnum;
}

/*Get the Letter P or Q or Y, is the product.*/
char getRandomLetter()
{
	char letterMap[4] = { 'P','Q','Y','\0' };
	int randNum;
	//srand((unsigned)(GetCurrentProcessId() + time(NULL)));
	randNum = rand() % 3;

	return letterMap[randNum];
}

/*Make shared memory.*/
HANDLE MakeSharedMem()
{
	/*Make view of file.*/
	HANDLE fMapping = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(struct sharedMem), sharedMemName);
	if (fMapping != INVALID_HANDLE_VALUE)
	{
		LPVOID pData = MapViewOfFile(fMapping, FILE_MAP_ALL_ACCESS, 0, 0, 0);
		if (pData != NULL)
		{
			memset(pData, 0, sizeof(struct sharedMem));
		}
		UnmapViewOfFile(pData);
	}

	return fMapping;
}

/*Clone the Process.*/
void cloneChildProcess(int nCloneID)
{
	TCHAR szFilename[MAX_PATH];
	TCHAR szCmdLine[MAX_PATH];
	char tempFilename[MAX_PATH];
	char tempCmdLine[MAX_PATH];
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	GetModuleFileName(NULL, szFilename, MAX_PATH);
	TCHAR_to_char(szFilename, tempFilename);
	sprintf(tempCmdLine, "\"%s\" %d", tempFilename, nCloneID);
	char_to_TCHAR(tempCmdLine, szCmdLine);
	memset(&si, 0, sizeof(si));
	si.cb = sizeof(si);

	/*Create Child Process.*/
	BOOL bCreateOK = CreateProcess(
		szFilename,
		szCmdLine,
		NULL,
		NULL,
		FALSE,
		0,
		NULL,
		NULL,
		&si,
		&pi
	);
	hChildProcess[nCloneID] = pi.hProcess;

	return;
}

/*Change TCHAR to char*/
void TCHAR_to_char(const TCHAR * tchar, char * _char)
{
	int iLength;
 
	iLength = WideCharToMultiByte(CP_ACP, 0, tchar, -1, NULL, 0, NULL, NULL);	//Get the length.
	WideCharToMultiByte(CP_ACP, 0, tchar, -1, _char, iLength, NULL, NULL);	//Give tchar value to _char.
}

/*Change char to TCHAR*/
void char_to_TCHAR(const char * _char, TCHAR * tchar)
{
	int iLength;

	iLength = MultiByteToWideChar(CP_ACP, 0, _char, strlen(_char) + 1, NULL, 0);
	MultiByteToWideChar(CP_ACP, 0, _char, strlen(_char) + 1, tchar, iLength);
}
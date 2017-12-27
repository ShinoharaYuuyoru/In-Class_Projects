#include <Windows.h>
#include <stdio.h>
#include <tchar.h>

BOOL myCreateDirectory(TCHAR *source, TCHAR *target);
BOOL myGetFileTime(TCHAR *Directory, FILETIME *CreationTime, FILETIME *LastAccessTime, FILETIME *LastWriteTime);
BOOL mySetFileTime(TCHAR *Directory, FILETIME *CreationTime, FILETIME *LastAccessTime, FILETIME *LastWriteTime);
BOOL myCopy(TCHAR *source, TCHAR *target);
BOOL myCopyFiles(TCHAR *source, TCHAR *target, DWORD size);

int _tmain(int argc, TCHAR * argv[])
{
	if (argc != 3)	//Number of parameters invalid.
	{
		printf("argc Error!\n");

		return 1;
	}

	WIN32_FIND_DATA FindSourceFileData;
	WIN32_FIND_DATA FindTargetFileData;

	if (FindFirstFile(argv[1], &FindSourceFileData) == INVALID_HANDLE_VALUE)
	{
		printf("Source Folder Address Error!\n");

		return 1;
	}
	else
	{
		if (FindFirstFile(argv[2], &FindTargetFileData) == INVALID_HANDLE_VALUE)
		{
			BOOL mycreateFlag = myCreateDirectory(argv[1], argv[2]);
			if (mycreateFlag == FALSE)
			{
				printf("myCreateDirectory Error!\n");

				return 1;
			}
		}

		BOOL mycopyFlag = myCopy(argv[1], argv[2]);
		if (mycopyFlag == FALSE)
		{
			printf("myCopy Error!\n");

			return 1;
		}
	}

	printf("Copy Files Finished.\n");

	return 0;
}

/*Create the first directory*/
BOOL myCreateDirectory(TCHAR *source, TCHAR *target)
{
	FILETIME CreationTime;
	FILETIME LastAccessTime;
	FILETIME LastWriteTime;

	BOOL createFlag = CreateDirectory(target, NULL);
	
	BOOL getTimeFlag = myGetFileTime(source, &CreationTime, &LastAccessTime, &LastWriteTime);
	BOOL setTimeFlag = mySetFileTime(target, &CreationTime, &LastAccessTime, &LastWriteTime);

	return (createFlag&getTimeFlag&setTimeFlag);
}

/*Get the file(folder) time information*/
BOOL myGetFileTime(TCHAR *Directory, FILETIME *CreationTime, FILETIME *LastAccessTime, FILETIME *LastWriteTime)
{
	HANDLE hDirectory = CreateFile(Directory, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);	//For directory, must set FILE_FLAG_BACKUP_SEMANTICS

	BOOL Flag = GetFileTime(hDirectory, CreationTime, LastAccessTime, LastWriteTime);

	CloseHandle(hDirectory);

	return Flag;
}

/*Set the file(folder) time information*/
BOOL mySetFileTime(TCHAR *Directory, FILETIME *CreationTime, FILETIME *LastAccessTime, FILETIME *LastWriteTime)
{
	HANDLE hDirectory = CreateFile(Directory, GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);	//For directory, must set FILE_FLAG_BACKUP_SEMANTICS

	BOOL Flag = SetFileTime(hDirectory, CreationTime, LastAccessTime, LastWriteTime);

	CloseHandle(hDirectory);

	return Flag;
}

/*Copy files(folders), recursion*/
BOOL myCopy(TCHAR *source, TCHAR *target)
{
	TCHAR fileSource[MAX_PATH];
	TCHAR fileTarget[MAX_PATH];

	_tcscpy(fileSource, source);
	_tcscat(fileSource, TEXT("\\*.*"));
	_tcscpy(fileTarget, target);
	_tcscat(fileTarget, TEXT("\\"));

	WIN32_FIND_DATA FindFileData;
	HANDLE hFile = FindFirstFile(fileSource, &FindFileData);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	else
	{
		while (FindNextFile(hFile, &FindFileData))
		{
			if ((_tcscmp(FindFileData.cFileName, TEXT(".")) != 0) && (_tcscmp(FindFileData.cFileName, TEXT("..")) != 0))	//If the directory or file name valid
			{
				if (FindFileData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY|| FindFileData.dwFileAttributes == 8208)
				{
					/*If the file is child directory*/
					/*This is the Folder Copy segment*/

					memset(fileSource, 0, sizeof(fileSource));
					_tcscpy(fileSource, source);
					_tcscat(fileSource, TEXT("\\"));

					/*Add the folder name to the directory*/
					_tcscat(fileSource, FindFileData.cFileName);
					_tcscat(fileTarget, FindFileData.cFileName);

					/*Create the folder*/
					myCreateDirectory(fileSource, fileTarget);

					/*Recursion*/
					BOOL myCFlag = myCopy(fileSource, fileTarget);
					if (myCFlag == FALSE)
					{
						printf("myCopy Error!\n");

						return FALSE;
					}

					/*Return to parent directory*/
					memset(fileSource, 0, sizeof(fileSource));
					_tcscpy(fileSource, source);
					_tcscat(fileSource, TEXT("\\"));
					memset(fileTarget, 0, sizeof(fileTarget));
					_tcscpy(fileTarget, target);
					_tcscat(fileTarget, TEXT("\\"));
				}
				else
				{
					/*If the file is the FILE*/
					/*This is the file copy segment*/

					memset(fileSource, 0, sizeof(fileSource));
					_tcscpy(fileSource, source);
					_tcscat(fileSource, TEXT("\\"));

					/*Add the file name to the directory*/
					_tcscat(fileSource, FindFileData.cFileName);
					_tcscat(fileTarget, FindFileData.cFileName);

					BOOL myCFFlag = myCopyFiles(fileSource, fileTarget, FindFileData.nFileSizeLow);	//Only used for 32bit OS.
					if (myCFFlag == FALSE)
					{
						printf("myCopyFiles Error!\n");

						return FALSE;
					}

					/*Return to directory*/
					memset(fileSource, 0, sizeof(fileSource));
					_tcscpy(fileSource, source);
					_tcscat(fileSource, TEXT("\\"));
					memset(fileTarget, 0, sizeof(fileTarget));
					_tcscpy(fileTarget, target);
					_tcscat(fileTarget, TEXT("\\"));
				}
			}
		}
	}

	return TRUE;
}

/*Just copy the file, only used for 32bit OS.*/
BOOL myCopyFiles(TCHAR *source, TCHAR *target, DWORD size)
{
	HANDLE hSourceFile = CreateFile(source, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	HANDLE hTargetFile = CreateFile(target, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	DWORD fileSize = size;
	char *Buffer = new char[fileSize + 1];
	DWORD readSize;

	BOOL RFFlag = ReadFile(hSourceFile, Buffer, fileSize, &readSize, NULL);
	BOOL WFFlag = WriteFile(hTargetFile, Buffer, fileSize, &readSize, NULL);

	delete[]Buffer;

	CloseHandle(hTargetFile);
	CloseHandle(hSourceFile);

	return (RFFlag&WFFlag);
}
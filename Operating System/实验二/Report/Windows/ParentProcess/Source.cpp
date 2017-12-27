#include <stdio.h>
#include <Windows.h>
#include <tchar.h>

/*Day of Week Format*/
TCHAR arrDayofWeek[7][4] =
{
	TCHAR("Sun"),
	TCHAR("Mon"),
	TCHAR("Tue"),
	TCHAR("Wed"),
	TCHAR("Thu"),
	TCHAR("Fri"),
	TCHAR("Sat"),
};

void _tmain(int argc, TCHAR *argv[])
{
	SYSTEMTIME startTime, endTime;

	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	memset(&si, 0, sizeof(si));
	si.cb = sizeof(si);
	memset(&pi, 0, sizeof(pi));

	if (argc != 2)
	{
		printf("Usage: %s [cmdline]\n", argv[0]);
		return;
	}

	if (!CreateProcess
		(
			NULL,
			argv[1],
			NULL,
			NULL,
			FALSE,
			0,
			NULL,
			NULL,
			&si,
			&pi
		)
	)
	{
		printf("CreateProcess failed (%d).\n", GetLastError());
		return;
	}
	else
	{
		printf("CreateProcess Success!\n");
		GetSystemTime(&startTime);
		printf("ChildProcess started at %04d.%02d.%02d %s %02d:%02d:%02d.%04d UTC.\n", startTime.wYear, startTime.wMonth, startTime.wDay, arrDayofWeek[startTime.wDayOfWeek], startTime.wHour, startTime.wMinute, startTime.wSecond, startTime.wMilliseconds);
	}

	WaitForSingleObject(pi.hProcess, INFINITE);
	GetSystemTime(&endTime);
	printf("ChildProcess ended at %04d.%02d.%02d %s %02d:%02d:%02d.%04d UTC.\n", endTime.wYear, endTime.wMonth, endTime.wDay, arrDayofWeek[endTime.wDayOfWeek], endTime.wHour, endTime.wMinute, endTime.wSecond, endTime.wMilliseconds);

	int milliseconds, seconds, minutes;
	milliseconds = endTime.wMilliseconds - startTime.wMilliseconds;
	seconds = endTime.wSecond - startTime.wSecond;
	minutes = endTime.wMinute - startTime.wMinute;
	if (milliseconds < 0)
	{
		milliseconds = milliseconds + 1000;
		seconds--;
	}
	if (seconds < 0)
	{
		seconds = seconds + 60;
	}
	if (minutes < 0)
	{
		minutes = minutes + 60;
	}
	printf("ChildProcess used %ds%dms.\n", seconds, milliseconds);

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}
#include <Windows.h>
#include <Psapi.h>
#include <tchar.h>
#include <stdio.h>
#include <conio.h>
#include <TlHelp32.h>

void ShowSysInfo();
void ShowPerformanceInfo();
void ShowPhysicalMemoryInfo();
void ShowTHISProcInfo();
void ShowVirtualMemInfo(HANDLE hProcess);
void ShowWorkingSetInfo(int PID);
void GetConsoleCursorXY(int &x, int &y);
void SetConsoleCursorTo(int x, int y);

int MonitorPID = -1;

int main()
{
Restart:
	printf("Please Input the PID to monitor a process.\n");
	printf("If don't want to monitor any process, please input -1.\n");
	scanf("%d", &MonitorPID);

	if (MonitorPID == -1)
	{
		int SelectNum;

		printf("1. Show System Information.\n");
		printf("2. Show Performance Infomation.\n");
		printf("3. Show Physical Memory Information.\n");
		printf("Please input the number to select.\n");

		scanf("%d", &SelectNum);
		switch (SelectNum)
		{
		case 1:ShowSysInfo();break;
		case 2:ShowPerformanceInfo();break;
		case 3:ShowPhysicalMemoryInfo();break;
		default:printf("Input Error!\n");break;
		}

		printf("\nPlease input the command:\n");
		printf("[0] Restart the monitor.\n");
		printf("Other key to close the monitor.\n");
		int command = -1;
		scanf("%d", &command);
		if (command == 0)
		{
			goto Restart;
		}
		else
		{
			printf("Thank you for using.\n");
		}
	}
	else
	{
		int SelectNum;

		printf("1. Show System Information.\n");
		printf("2. Show Performance Infomation.\n");
		printf("3. Show Physical Memory Information.\n");
		printf("4. Show This Process Information, includes Virtual Memory Information and Working Set Information.\n");
		printf("Please input the number to select.\n");

		scanf("%d", &SelectNum);
		switch (SelectNum)
		{
		case 1:ShowSysInfo();break;
		case 2:ShowPerformanceInfo();break;
		case 3:ShowPhysicalMemoryInfo();break;
		case 4:ShowTHISProcInfo();break;
		default:printf("Input Error!\n");break;
		}

		printf("\nPlease input the command:\n");
		printf("[0] Restart the monitor.\n");
		printf("Other key to close the monitor.\n");
		int command = -1;
		scanf("%d", &command);
		if (command == 0)
		{
			goto Restart;
		}
		else
		{
			printf("Thank you for using.\n");
		}
	}
}

/*Show System Info*/
void ShowSysInfo()
{
	SYSTEM_INFO SystemInfo;
	int X = 0, Y = 0, flag = 0;	//Cursor Position

	ZeroMemory(&SystemInfo, sizeof(SystemInfo));

	while (kbhit() == 0)
	{
		if (flag == 0)
		{
			GetConsoleCursorXY(X, Y);
			flag = 1;
		}
		else
		{
			SetConsoleCursorTo(X, Y);
		}

		GetSystemInfo(&SystemInfo);

		printf("Hardware information:\n");
		printf("OEM ID: %u\n", SystemInfo.dwOemId);	//1. OEM ID
		printf("Processor Architecture: ");	//2. Processor Architecture
		switch (SystemInfo.wProcessorArchitecture)
		{
		case 0:printf("x86\n");break;
		case 5:printf("ARM\n");break;
		case 6:printf("Intel Itanium-based\n");break;
		case 9:printf("x64 (AMD or Intel)\n");break;
		case 0xffff:printf("Unknown architecture.\n");break;
		}
		printf("Page Size(Bytes): %u\n", SystemInfo.dwPageSize);	//3. Page Size
		printf("Minimum Application Address: 0x%lx\n", SystemInfo.lpMinimumApplicationAddress);	//4. Minimum Application Address
		printf("Maximum Application Address: 0x%lx\n", SystemInfo.lpMaximumApplicationAddress);	//5. Maximum Application Address
		printf("Size of Application's usable virtual memory(Bytes): %u\n", ((DWORD)SystemInfo.lpMaximumApplicationAddress - (DWORD)SystemInfo.lpMinimumApplicationAddress));	//Extend. Size of Application's usable virtual memory
		printf("Active Processor Mask: %u\n", SystemInfo.dwActiveProcessorMask);	//6. Active Processor Mask
		printf("Number of Processors: %u\n", SystemInfo.dwNumberOfProcessors);	//7. Number of Processors
		printf("Processor Type: %u\n", SystemInfo.dwProcessorType);	//8. Processor Type
		printf("Allocation Granularity: %u\n", SystemInfo.dwAllocationGranularity);	//9. Allocation Granularity
		printf("Processor Level: %u\n", SystemInfo.wProcessorLevel);	//10. Processor Level
		printf("Processor Revision: %u\n", SystemInfo.wProcessorRevision);	//11. "Processor Revision

		printf("\n*****Press <ESC> to stop.*****\n");

		Sleep(1000);	//Refresh per second.
	}
}

/*Show Performance Info*/
void ShowPerformanceInfo()
{
	PERFORMANCE_INFORMATION PerformanceInfo;
	int X = 0, Y = 0, flag = 0;	//Cursor Position

	ZeroMemory(&PerformanceInfo, sizeof(PerformanceInfo));
	PerformanceInfo.cb = sizeof(PerformanceInfo);

	while (kbhit() == 0)
	{
		if (flag == 0)
		{
			GetConsoleCursorXY(X, Y);
			flag = 1;
		}
		else
		{
			SetConsoleCursorTo(X, Y);
		}

		GetPerformanceInfo(&PerformanceInfo, PerformanceInfo.cb);

		printf("CommitTotal(pages): %u\n", PerformanceInfo.CommitTotal);	//1. The number of pages currently committed by the system.
		printf("CommitLimit(pages): %u\n", PerformanceInfo.CommitLimit);	//2. The current maximum number of pages that can be committed by the system without extending the paging file(s).
		printf("CommitPeak(pages): %u\n", PerformanceInfo.CommitPeak);	//3. The maximum number of pages that were simultaneously in the committed state since the last system reboot.
		printf("PhysicalTotal(pages): %u\n", PerformanceInfo.PhysicalTotal);	//4. The amount of actual physical memory, in pages.
		printf("PhysicalAvailable(pages): %u\n", PerformanceInfo.PhysicalAvailable);	//5. The amount of physical memory currently available, in pages.
		printf("SystemCache(pages): %u\n", PerformanceInfo.SystemCache);	//6. The amount of system cache memory, in pages.
		printf("KernelTotal(pages): %u\n", PerformanceInfo.KernelTotal);	//7. The sum of the memory currently in the paged and nonpaged kernel pools, in pages.
		printf("KernelPaged(pages): %u\n", PerformanceInfo.KernelPaged);	//8. The memory currently in the paged kernel pool, in pages.
		printf("KernelNonpaged(pages): %u\n", PerformanceInfo.KernelNonpaged);	//9. The memory currently in the nonpaged kernel pool, in pages.
		printf("PageSize(Bytes): %u\n", PerformanceInfo.PageSize);	//10. The size of a page, in bytes.
		printf("HandleCount: %u\n", PerformanceInfo.HandleCount);	//11. The current number of open handles.
		printf("ProcessCount: %u\n", PerformanceInfo.ProcessCount);	//12. The current number of processes.
		printf("ThreadCount: %u\n", PerformanceInfo.ThreadCount);	//13. The current number of threads.

		printf("\n*****Press <ESC> to stop.*****\n");

		Sleep(1000);	//Refresh per second.
	}
}

/*Show Physical Memory Info*/
void ShowPhysicalMemoryInfo()
{
	MEMORYSTATUSEX MemoryStatusEX;
	int X = 0, Y = 0, flag = 0;	//Cursor Position

	ZeroMemory(&MemoryStatusEX, sizeof(MemoryStatusEX));
	MemoryStatusEX.dwLength = sizeof(MemoryStatusEX);

	while (kbhit() == 0)
	{
		if (flag == 0)
		{
			GetConsoleCursorXY(X, Y);
			flag = 1;
		}
		else
		{
			SetConsoleCursorTo(X, Y);
		}

		GlobalMemoryStatusEx(&MemoryStatusEX);

		printf("There is %ld percent of memory in use.\n", MemoryStatusEX.dwMemoryLoad);
		printf("There are %I64d total KB of physical memory.\n", MemoryStatusEX.ullTotalPhys / 1024);
		printf("There are %I64d free KB of physical memory.\n", MemoryStatusEX.ullAvailPhys / 1024);
		printf("There are %I64d total KB of paging file.\n", MemoryStatusEX.ullTotalPageFile / 1024);
		printf("There are %I64d free KB of paging file.\n", MemoryStatusEX.ullAvailPageFile / 1024);
		printf("There are %I64d total KB of virtual memory.\n", MemoryStatusEX.ullTotalVirtual / 1024);
		printf("There are %I64d free KB of virtual memory.\n", MemoryStatusEX.ullAvailVirtual / 1024);

		// Show the amount of extended memory available.
		printf("There are %I64d free KB of extended memory.\n", MemoryStatusEX.ullAvailExtendedVirtual / 1024);

		printf("\n*****Press <ESC> to stop.*****\n");

		Sleep(1000);	//Refresh per second.
	}
}

/*Show THIS Process Info, includes Virtual Memory Info and Working Set Info*/
void ShowTHISProcInfo()
{
	int THISPID = MonitorPID;
	HANDLE hTHISProcess;
	int X = 0, Y = 0, flag = 0;	//Cursor Position

	//THISPID = GetCurrentProcessId();
	hTHISProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, THISPID);

	while (kbhit() == 0)
	{
		if (hTHISProcess != NULL)
		{
			if (flag == 0)
			{
				GetConsoleCursorXY(X, Y);
				flag = 1;
			}
			else
			{
				SetConsoleCursorTo(X, Y);
			}

			ShowVirtualMemInfo(hTHISProcess);
			ShowWorkingSetInfo(THISPID);

			printf("\n*****Press <ESC> to stop.*****\n");
			printf("*****Close the monitor first, then close The Process.*****\n");

			Sleep(1000);	//Refresh per second.
		}
		else
		{
			printf("The Process was not exist. The monitor will close.\n");

			return;
		}
	}
}

/*Show THE PROCESS's Virtual Memory Info*/
void ShowVirtualMemInfo(HANDLE hProcess)
{
	SYSTEM_INFO SI;
	MEMORY_BASIC_INFORMATION MBI;

	ZeroMemory(&SI, sizeof(SI));
	ZeroMemory(&MBI, sizeof(MBI));

	GetSystemInfo(&SI);
	LPCVOID pBlock = (LPVOID)SI.lpMinimumApplicationAddress;

	while (pBlock < SI.lpMaximumApplicationAddress)
	{
		if (VirtualQueryEx(hProcess, pBlock, &MBI, sizeof(MBI)) == sizeof(MBI))
		{
			LPCVOID pEnd = (PBYTE)pBlock + MBI.RegionSize;
			printf("Block starts at: 0x%lx, ", pBlock);	//1. Show Block Starts Addr.
			printf("Block Length(Bytes): %u, ", MBI.RegionSize);	//2. Show Block's length.
			switch (MBI.State)	//3. Show Block's State.
			{
			case MEM_COMMIT:
				printf("Committed, ");break;
			case MEM_FREE:
				printf("Free.\n");break;
			case MEM_RESERVE:
				printf("Reserved, ");break;
			}
			switch (MBI.Type)	//4. Show Block's Type.
			{
			case MEM_IMAGE:
				printf("Image.\n");break;
			case MEM_MAPPED:
				printf("Mapped.\n");break;
			case MEM_PRIVATE:
				printf("Private.\n");break;
			}

			pBlock = pEnd;
		}
		else
		{
			break;
		}
	}
}

/*Show THE PROCESS's Working Set Info*/
void ShowWorkingSetInfo(int PID)
{
	PROCESSENTRY32 PE32;
	PROCESS_MEMORY_COUNTERS ProcMemCounter;
	HANDLE hProcessSnap;

	ZeroMemory(&PE32, sizeof(PE32));
	ZeroMemory(&ProcMemCounter, sizeof(ProcMemCounter));
	PE32.dwSize = sizeof(PE32);
	ProcMemCounter.cb = sizeof(ProcMemCounter);

	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	BOOL bNext = Process32First(hProcessSnap, &PE32);
	printf("Process Working Set Information:\n");
	while (bNext)
	{
		if (PID == PE32.th32ProcessID)
		{
			HANDLE hProcess;
			hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);
			GetProcessMemoryInfo(hProcess, &ProcMemCounter, sizeof(ProcMemCounter));
			printf("Commited(Bytes): %u\n", ProcMemCounter.PagefileUsage);
			printf("Working Set Size(Byte): %u\n", ProcMemCounter.WorkingSetSize);
			printf("Peak Working Set Size(Byte): %u\n", ProcMemCounter.PeakWorkingSetSize);

			break;
		}

		bNext = Process32Next(hProcessSnap, &PE32);
	}
}

/*Get console cursor's position*/
void GetConsoleCursorXY(int &x, int &y)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO CSBI;

	GetConsoleScreenBufferInfo(hConsole, &CSBI);

	x = CSBI.dwCursorPosition.X;
	y = CSBI.dwCursorPosition.Y;
}

/*Set console cursor to (x, y)*/
void SetConsoleCursorTo(int x, int y)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD SetCursorPosition = { x, y };

	SetConsoleCursorPosition(hConsole, SetCursorPosition);
}
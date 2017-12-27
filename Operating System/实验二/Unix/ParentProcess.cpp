#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <time.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	struct timeval startTime;
	struct timeval endTime;
	int seconds, milliseconds;	//Used for printing usedTime
	
	pid_t pid;
	char *exec_argv[4];
	int i;
	
	if(argc != 2)
	{
		printf("argc Error!\n");
		printf("CreateProcess failed.\n");
		return 0;
	}
	
	pid = fork();
	
	if(pid==0)	//ChildProcess goes to here
	{
		for(i = 0; i<argc; i++)
		{
			exec_argv[i] = argv[i+1];	//argv[0]:ParentProcess, argv[1]:ChildProcess argv[2]:NULL
		}	//exec_argv[0]:ChildProcess, exec_argv[1]:NULL

		printf("CreateProcess Success!\n");
		execv(argv[1], exec_argv);	//execv("ChildProcess", exec_argv);
	}
	else	//ParentProcess goes to here
	{
		gettimeofday(&startTime, NULL);
		printf("%sAt %04ldms UTC.\n", asctime(gmtime(&startTime.tv_sec)), startTime.tv_usec/1000);
		
		wait(NULL);	//Wait for ChildProcess's signal
		
		gettimeofday(&endTime, NULL);
		printf("%sAt %04ldms UTC.\n", asctime(gmtime(&endTime.tv_sec)), endTime.tv_usec/1000);
		seconds = (1000000 * ( endTime.tv_sec - startTime.tv_sec ) + (endTime.tv_usec - startTime.tv_usec))/1000000;
		milliseconds = (endTime.tv_usec - startTime.tv_usec)/1000;
		printf("ChildProcess used %ds%dms.\n", seconds, milliseconds);
	}
	
	return 0;
}

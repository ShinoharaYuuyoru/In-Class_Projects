#include <WinSock2.h>
#include <stdio.h>
#include <string.h>

#define MAX_SIZE 256
#define RESPOND_MAX_SIZE 65536

WSADATA wsaData;
int sock;
char hostName[MAX_SIZE] = "pop3.sina.com";			// Host Name(Sina).
struct hostent* pHost;
struct sockaddr_in servAddr;
int byteRcvd;						// Received byte.
char respondFromServer[RESPOND_MAX_SIZE];	// Received data.
char inputString[MAX_SIZE];			// Input string.
char command[MAX_SIZE];				// Commands to send.

void POP3_LIST();
void POP3_UIDL();
void POP3_RETR();
void POP3_DELE();
void POP3_RSET();
int POP3_QUIT();

int main()
{
	printf("***** This is a POP3 Mail Receiver for Sina Mail. *****\n");

	// WSAWtartup
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		printf("WSAStartup failed.\n");

		exit(1);
	}

	// Socket building
	sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET)
	{
		printf("Socket building failed.\n");

		WSACleanup();
		exit(1);
	}

	// Get host IP and set host infomation. Connect.
	pHost = gethostbyname(hostName);
	memset(&servAddr, 0, sizeof(servAddr));				// Initial.
	servAddr.sin_family = AF_INET;
	memcpy(&servAddr.sin_addr.S_un.S_addr, pHost->h_addr_list[0], pHost->h_length);
	servAddr.sin_port = htons(110);
	if (connect(sock, (struct sockaddr*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
	{
		printf("Connection failed.\n");

		closesocket(sock);
		WSACleanup();
		exit(1);
	}

	// Start Connecting.
	byteRcvd = recv(sock, respondFromServer, RESPOND_MAX_SIZE, 0);
	respondFromServer[byteRcvd] = '\0';
	printf("Server: %s\n", respondFromServer);

	// Authentication.
	// Username
	memset(inputString, 0, sizeof(inputString));			// Initial.
	memset(command, 0, MAX_SIZE);
	printf("Client: Please input username:\n");
	scanf("%s", inputString);
	strcpy(command, "USER ");
	strcat(command, inputString);
	strcat(command, "\r\n");
	send(sock, command, strlen(command), 0);
	byteRcvd = recv(sock, respondFromServer, RESPOND_MAX_SIZE, 0);
	respondFromServer[byteRcvd] = '\0';
	printf("Server: %s\n", respondFromServer);

	// Password
	memset(inputString, 0, sizeof(inputString));
	memset(command, 0, MAX_SIZE);
	printf("Client: Please input password:\n");
	scanf("%s", inputString);
	strcpy(command, "PASS ");
	strcat(command, inputString);
	strcat(command, "\r\n");
	send(sock, command, strlen(command), 0);
	byteRcvd = recv(sock, respondFromServer, RESPOND_MAX_SIZE, 0);
	respondFromServer[byteRcvd] = '\0';
	printf("Server: %s\n", respondFromServer);

	// Print mail statics.
	memset(command, 0, MAX_SIZE);
	strcpy(command, "STAT\r\n");
	printf("Client: STAT...\n");
	send(sock, command, strlen(command), 0);
	byteRcvd = recv(sock, respondFromServer, RESPOND_MAX_SIZE, 0);
	respondFromServer[byteRcvd] = '\0';
	printf("Server: %s\n", respondFromServer);

	int chooseFlag = 0;						// Choose option Flag.

	while (1)
	{
		int quitFlag = 0;

		printf("Client: Please choose the option.\n");
		printf("\t1 - LIST (List the mail infomation.)\n");
		printf("\t2 - UIDL (Check the mail's UID.)\n");
		printf("\t3 - RETR (Read the mail.)\n");
		printf("\t4 - DELE (Mark the delete sign to the mail and it will be deleted when quit.)\n");
		printf("\t5 - RSET (Reset the delete sign.)\n");
		printf("\t6 - QUIT\n");

		scanf("%d", &chooseFlag);
		switch (chooseFlag)
		{
		case 1:POP3_LIST();break;
		case 2:POP3_UIDL();break;
		case 3:POP3_RETR();break;
		case 4:POP3_DELE();break;
		case 5:POP3_RSET();break;
		case 6:
			if (POP3_QUIT() == 0)
			{
				quitFlag = 1;
			}
			;break;
		}

		if (quitFlag == 1)
		{
			break;
		}
	}

	return 0;
}

void POP3_LIST()
{
	int inputNumber = 0;
	printf("Client: Please input the number of mail which you want to list.\n");
	printf("\t0: To list all mails. (If you can't get the list, please retry.)\n");
	printf("\t1 or bigger: To list the mail you want to list.\n");
	scanf("%d", &inputNumber);

	if (inputNumber == 0)
	{
		memset(command, 0, MAX_SIZE);
		strcpy(command, "LIST\r\n");
		send(sock, command, strlen(command), 0);
		printf("Client: This is the statics of all mails.\n");
		byteRcvd = recv(sock, respondFromServer, RESPOND_MAX_SIZE, 0);
		respondFromServer[byteRcvd] = '\0';
		printf("Server: %s", respondFromServer);
		byteRcvd = recv(sock, respondFromServer, RESPOND_MAX_SIZE, 0);
		respondFromServer[byteRcvd] = '\0';
		printf("Server: %s\n", respondFromServer);
	}
	else
	{
		char inputNumberStr[8];
		itoa(inputNumber, inputNumberStr, 10);

		memset(command, 0, MAX_SIZE);
		strcpy(command, "LIST ");
		strcat(command, inputNumberStr);
		strcat(command, "\r\n");
		send(sock, command, strlen(command), 0);
		printf("Client: The No.%d mail you want to list:\n", inputNumber);
		byteRcvd = recv(sock, respondFromServer, RESPOND_MAX_SIZE, 0);
		respondFromServer[byteRcvd] = '\0';
		printf("Server: %s\n", respondFromServer);
	}
}

void POP3_UIDL()
{
	int inputNumber = 0;
	printf("Client: Please input the number of mail which you want to check UID.\n");
	printf("\t0: To print all mails' UID. (If you can't get all UIDs, please retry.)\n");
	printf("\t1 or bigger: To print the mail you want to check UID.\n");
	scanf("%d", &inputNumber);

	if (inputNumber == 0)
	{
		memset(command, 0, MAX_SIZE);
		strcpy(command, "UIDL\r\n");
		send(sock, command, strlen(command), 0);
		printf("Client: This is the statics of all mails.\n");
		byteRcvd = recv(sock, respondFromServer, RESPOND_MAX_SIZE, 0);
		respondFromServer[byteRcvd] = '\0';
		printf("Server: %s", respondFromServer);
		byteRcvd = recv(sock, respondFromServer, RESPOND_MAX_SIZE, 0);
		respondFromServer[byteRcvd] = '\0';
		printf("Server: %s\n", respondFromServer);
	}
	else
	{
		char inputNumberStr[8];
		itoa(inputNumber, inputNumberStr, 10);

		memset(command, 0, MAX_SIZE);
		strcpy(command, "UIDL ");
		strcat(command, inputNumberStr);
		strcat(command, "\r\n");
		send(sock, command, strlen(command), 0);
		printf("Client: The No.%d mail you want to check UID:\n", inputNumber);
		byteRcvd = recv(sock, respondFromServer, RESPOND_MAX_SIZE, 0);
		respondFromServer[byteRcvd] = '\0';
		printf("Server: %s\n", respondFromServer);
	}
}

void POP3_RETR()
{
	int inputNumber = 0;
	printf("Client: Please input the number of mail which you want to read.\n");
	scanf("%d", &inputNumber);

	if (inputNumber == 0)
	{
		printf("Client: Input Error!\n");
		return;
	}
	else
	{
		char inputNumberStr[8];
		itoa(inputNumber, inputNumberStr, 10);

		memset(command, 0, MAX_SIZE);
		strcpy(command, "RETR ");
		strcat(command, inputNumberStr);
		strcat(command, "\r\n");
		send(sock, command, strlen(command), 0);
		printf("Client: The No.%d mail you want to read:\n", inputNumber);
		byteRcvd = recv(sock, respondFromServer, RESPOND_MAX_SIZE, 0);
		respondFromServer[byteRcvd] = '\0';
		printf("Server: %s", respondFromServer);
		byteRcvd = recv(sock, respondFromServer, RESPOND_MAX_SIZE, 0);
		respondFromServer[byteRcvd] = '\0';
		printf("Server: %s\n", respondFromServer);
	}
}

void POP3_DELE()
{
	int inputNumber = 0;
	printf("Client: Please input the number of mail which you want to mark DELETE sign.\n");
	scanf("%d", &inputNumber);

	if (inputNumber == 0)
	{
		printf("Client: Input Error!\n");
		return;
	}
	else
	{
		char inputNumberStr[8];
		itoa(inputNumber, inputNumberStr, 10);

		memset(command, 0, MAX_SIZE);
		strcpy(command, "DELE ");
		strcat(command, inputNumberStr);
		strcat(command, "\r\n");
		send(sock, command, strlen(command), 0);
		printf("Client: The No.%d mail you want to mark DELETE sign:\n", inputNumber);
		byteRcvd = recv(sock, respondFromServer, RESPOND_MAX_SIZE, 0);
		respondFromServer[byteRcvd] = '\0';
		printf("Server: %s\n", respondFromServer);
	}
}

void POP3_RSET()
{
	char inputChar;
	printf("Do you want to reset all DELETE signs? [y/n]\n");
	getchar();
	scanf("%c", &inputChar);

	if (inputChar == 'n')
	{
		return;
	}
	else
	{
		if (inputChar == 'y')
		{
			memset(command, 0, MAX_SIZE);
			strcpy(command, "RSET\r\n");
			send(sock, command, strlen(command), 0);
			printf("Client: Reset all DELETE signs.\n");
			byteRcvd = recv(sock, respondFromServer, RESPOND_MAX_SIZE, 0);
			respondFromServer[byteRcvd] = '\0';
			printf("Server: %s\n", respondFromServer);
		}
		else
		{
			printf("Input Error!\n");

			return;
		}
	}
}

int POP3_QUIT()
{
	char inputChar;
	printf("Do you want to QUIT? (All mails marked DELETE will be deleted? [y/n]\n");
	getchar();
	scanf("%c", &inputChar);

	if (inputChar == 'n')
	{
		return 1;
	}
	else
	{
		if (inputChar == 'y')
		{
			memset(command, 0, MAX_SIZE);
			strcpy(command, "QUIT\r\n");
			send(sock, command, strlen(command), 0);
			printf("Client: Quit.\n");
			byteRcvd = recv(sock, respondFromServer, RESPOND_MAX_SIZE, 0);
			respondFromServer[byteRcvd] = '\0';
			printf("Server: %s\n", respondFromServer);

			return 0;
		}
		else
		{
			printf("Input Error!\n");

			return 1;
		}
	}
}
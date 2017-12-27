#define STR_MAX_SIZE 1024
#define HOST_PORT 80

#include <WinSock2.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>

using namespace std;

//#pragma comment (lib, "Ws2_32.lib")

int iResult;
char HostName[STR_MAX_SIZE];					// Host Name.
char recvBuffer[STR_MAX_SIZE];
char sendBuffer[STR_MAX_SIZE];
char tempIP[20];
char fileName[STR_MAX_SIZE];

void WriteFile(SOCKET& Sock, char* CMDParameter, char* recvbuff, char* sendbuff);

int main()
{
	printf("***** This is a simple HTML Page Downloader. *****\n");

	WSADATA wsaData;
	SOCKET sock;
	struct hostent* pHost;
	struct sockaddr_in ServerAddr;

	// Initial.
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) 
	{
		printf("WSAStartup failed.\n");

		return 1;
	}

	// Create Socket.
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET) 
	{
		printf("Socket building failed.\n");

		WSACleanup();
		return 1;
	}

	printf("Please input the an HTML page address you want to download(Without http://): ");
	gets_s(HostName);
	printf("Please input the name you want to save the HTML page as: ");
	gets_s(fileName);

	// Get host by name.
	pHost = gethostbyname(HostName);
	memset(&ServerAddr, 0, sizeof(ServerAddr));
	ServerAddr.sin_family = AF_INET;
	memcpy(&ServerAddr.sin_addr.S_un.S_addr, pHost->h_addr_list[0], pHost->h_length);
	ServerAddr.sin_port = htons(HOST_PORT);

	// Connect.
	if (connect(sock, (struct sockaddr*)&ServerAddr, sizeof(ServerAddr)) == SOCKET_ERROR) 
	{
		printf("Connection failed.\n");

		closesocket(sock);
		WSACleanup();
		return 1;
	}

	// Send the Download request.
	strcpy(sendBuffer, "GET / HTTP/1.1\r\n");
	strcat(sendBuffer, "Host:");
	itoa(ServerAddr.sin_addr.S_un.S_un_b.s_b1, tempIP, 10);
	strcat(sendBuffer, tempIP);
	strcat(sendBuffer, ".");
	itoa(ServerAddr.sin_addr.S_un.S_un_b.s_b2, tempIP, 10);
	strcat(sendBuffer, tempIP);
	strcat(sendBuffer, ".");
	itoa(ServerAddr.sin_addr.S_un.S_un_b.s_b3, tempIP, 10);
	strcat(sendBuffer, tempIP);
	strcat(sendBuffer, ".");
	itoa(ServerAddr.sin_addr.S_un.S_un_b.s_b4, tempIP, 10);
	strcat(sendBuffer, tempIP);
	strcat(sendBuffer, "\r\n");
	strcat(sendBuffer, "Accept: */*\r\n\r\n");
	if (send(sock, sendBuffer, strlen(sendBuffer), 0) > 0)
	{
		printf("Client: %s", sendBuffer);
	}

	// Download the page.
	WriteFile(sock, fileName, recvBuffer, sendBuffer);

	// QUIT
	closesocket(sock);
	WSACleanup();
	return 0;
}

void WriteFile(SOCKET& Sock, char* CMDParameter, char* recvbuff, char* sendbuff)
{

	int flag = 0;
	int flag2 = 0;
	int i = 0;

	ofstream OutFile(CMDParameter);

	printf("Client: Receive from server:\n");

	while (1)
	{
		char* writeFileBuffer = "";
		ZeroMemory(recvbuff, STR_MAX_SIZE);

		if ((iResult = recv(Sock, recvbuff, STR_MAX_SIZE, 0)) > 0) 
		{
			for (i = 0; recvbuff[i] != '\0'; i++) 
			{
				if (flag == 1)	// Check the HTML head over or not.
				{
					writeFileBuffer = &recvbuff[i];

					break;
				}

				if (recvbuff[i] == '\r'&&recvbuff[i + 1] == '\n'&&recvbuff[i + 2] == '\r'&&recvbuff[i + 3] == '\n')			// END OF \r\n\r\n
				{
					i = i + 3;
					flag = 1;
				}
				else 
				{
					printf("%c", recvbuff[i]);
				}

			}
			if (writeFileBuffer[0] != 0) 
			{
				OutFile.write(writeFileBuffer, strlen(writeFileBuffer) - strlen(sendbuff));
			}
		}
		else
		{
			printf("Client: error.\n");

			break;
		}
	}

	printf("\nDownload Completed.\n");

	OutFile.close();
}
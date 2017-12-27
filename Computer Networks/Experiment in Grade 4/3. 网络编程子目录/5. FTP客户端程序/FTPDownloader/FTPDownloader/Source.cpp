#define WIN32_LEAN_AND_MEAN
#define STR_MAX_LENGTH 1024
#define FTP_PORT "21"

#include <iostream>
#include <fstream>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

//#pragma comment (lib, "Ws2_32.lib")

int iResult;
WSADATA wsaData;
SOCKET sock = INVALID_SOCKET;
SOCKET dataSock = INVALID_SOCKET;
char FTPServerIP[STR_MAX_LENGTH] = "";
char ServerDataIP[STR_MAX_LENGTH] = "";
char ServerDataPort[STR_MAX_LENGTH] = "";

char CMDType[STR_MAX_LENGTH] = "";				// This is seperated by inputed sendBuffer.
char CMDParameter[STR_MAX_LENGTH] = "";			// This is seperated by inputed sendBuffer.
char sendBuffer[STR_MAX_LENGTH] = "";
char recvBuffer[STR_MAX_LENGTH] = "";

void ConnectSock(SOCKET& Sock, char* IP, char* Port);
void getCMDTypeAndParameter(char* CMD, char* CMDType, char* CMDParameter);
void SendAndRecv(SOCKET& Sock, char* sendbuff, char* recvbuff);
void WriteFile(SOCKET& Sock, char* CMDParameter, char* recvbuff);
void ReadFile(SOCKET& Sock, char* CMDParameter, char* sendbuff);
void GetDataIPAndPort(char* recvbuff, char* ServerDataIP, char* ServerDataPort);

int main()
{
	printf("***** This Program is based on FileZilla FTP Server. Please install FileZilla before test this program. *****\n");

	printf("Client: Please input FTP Server IP: ");
	gets_s(FTPServerIP);

	// Initial
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) 
	{
		printf("Client: WSAStartup failed with error: %d\n", iResult);
		return 1;
	}

	// Connect
	ConnectSock(sock, FTPServerIP, FTP_PORT);		// Port 21 to FTP

	iResult = recv(sock, recvBuffer, STR_MAX_LENGTH, 0);
	if (iResult > 0)
	{
		printf("Server: %s\n", recvBuffer);
	}
	iResult = recv(sock, recvBuffer, STR_MAX_LENGTH, 0);
	if (iResult > 0)
	{
		printf("Server: %s\n", recvBuffer);
	}

	// Start FTP Client
	while (1) 
	{
		ZeroMemory(sendBuffer, STR_MAX_LENGTH);
		ZeroMemory(recvBuffer, STR_MAX_LENGTH);

		printf("Client: Please input command. If you want to STOR or RETR, please run PASV first: ");
		gets_s(sendBuffer);
		getCMDTypeAndParameter(sendBuffer, CMDType, CMDParameter);
		strcat(sendBuffer, "\r\n");

		if (strcmp(CMDType, "USER") == 0) 
		{
			SendAndRecv(sock, sendBuffer, recvBuffer);
		}
		else if (strcmp(CMDType, "PASS") == 0) 
		{
			SendAndRecv(sock, sendBuffer, recvBuffer);
		}
		else if (strcmp(CMDType, "RETR") == 0)				// Download the file from Server
		{
			ConnectSock(dataSock, ServerDataIP, ServerDataPort);

			iResult = send(sock, sendBuffer, strlen(sendBuffer), 0);
			if (iResult <= 0)
			{
				printf("Client: send error.\n");

				return 1;
			}

			ZeroMemory(recvBuffer, STR_MAX_LENGTH);
			iResult = recv(sock, recvBuffer, STR_MAX_LENGTH, 0);
			if (iResult > 0)
			{
				printf("Server: %s", recvBuffer);
			}
			else
			{
				printf("Client: receive error.\n");
			}

			WriteFile(dataSock, CMDParameter, recvBuffer);

			ZeroMemory(recvBuffer, STR_MAX_LENGTH);
			iResult = recv(sock, recvBuffer, STR_MAX_LENGTH, 0);
			if (iResult > 0)
			{
				printf("Server: %s", recvBuffer);
			}
			else
			{
				printf("Client: receive error.\n");
			}
		}
		else if (strcmp(CMDType, "STOR") == 0)				// Store a file to Server
		{
			ConnectSock(dataSock, ServerDataIP, ServerDataPort);
			iResult = send(sock, sendBuffer, strlen(sendBuffer), 0);
			if (iResult <= 0)
			{
				printf("Client: send error.\n");
			}

			ZeroMemory(recvBuffer, STR_MAX_LENGTH);
			iResult = recv(sock, recvBuffer, STR_MAX_LENGTH, 0);
			if (iResult > 0)
			{
				printf("Server: %s", recvBuffer);
			}
			else
			{
				printf("Client: receive error.\n");
			}


			ReadFile(dataSock, CMDParameter, recvBuffer);

			ZeroMemory(recvBuffer, STR_MAX_LENGTH);
			iResult = recv(sock, recvBuffer, STR_MAX_LENGTH, 0);
			if (iResult > 0)
			{
				printf("Server: %s", recvBuffer);
			}
			else
			{
				printf("Client: receive error.\n");
			}

		}
		else if (strcmp(CMDType, "PASV") == 0)				// This is Passivity Mode.
		{
			SendAndRecv(sock, sendBuffer, recvBuffer);
			GetDataIPAndPort(recvBuffer, ServerDataIP, ServerDataPort);
		}
		else if (strcmp(CMDType, "QUIT") == 0)				// QUIT
		{
			SendAndRecv(sock, sendBuffer, recvBuffer);
			break;
		}
	}

	// Cleanup
	closesocket(sock);
	WSACleanup();
	return 0;
}

void ConnectSock(SOCKET& Sock, char* IP, char* Port) 
{
	int iResult;
	struct addrinfo *SockAddrInfo = NULL;
	struct addrinfo hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	iResult = getaddrinfo(IP, Port, &hints, &SockAddrInfo);
	if (iResult != 0) 
	{
		printf("getaddrinfo failed with error: %d\n", iResult);
		return;
	}
	Sock = socket(SockAddrInfo->ai_family, SockAddrInfo->ai_socktype, SockAddrInfo->ai_protocol);

	iResult = connect(Sock, SockAddrInfo->ai_addr, (int)SockAddrInfo->ai_addrlen);
	if (iResult != SOCKET_ERROR)
	{
		printf("Connect Successful.\n");
	}
}

// Seperate inputed Command to Command Type and Command Parameter.
void getCMDTypeAndParameter(char* CMD, char* CMDType, char* CMDParameter) {
	int i, j;
	for (i = 0; CMD[i] != 0; i++) 
	{
		CMDType[i] = CMD[i];
		if (CMD[i] == ' ') 
		{
			CMDType[i] = '\0';
			break;
		}
	}

	if (CMD[i] == 0)			// Only have Command Type
	{
		CMDType[i] = '\0';
		CMDParameter[0] = '\0';
	}
	else						// Command Type with Parameter.
	{
		i++;					// Jump the space to parameter.
		for (j = 0; CMD[i + j] != 0; j++) 
		{
			CMDParameter[j] = CMD[i + j];
		}
		CMDParameter[j] = '\0';
	}
}

// Send and Receive.
void SendAndRecv(SOCKET& Sock, char* sendbuff, char* recvbuff) 
{
	iResult = send(Sock, sendbuff, strlen(sendbuff), 0);
	if (iResult <= 0) 
	{
		printf("Client: send error.\n");
		return;
	}

	ZeroMemory(recvbuff, STR_MAX_LENGTH);
	iResult = recv(Sock, recvbuff, STR_MAX_LENGTH, 0);
	if (iResult > 0)
	{
		printf("Server: %s", recvbuff);
	}
	else 
	{
		printf("Client: receive error.\n");

		return;
	}
}

// Write the file downloaded from server.
void WriteFile(SOCKET& Sock, char* CMDParameter, char* recvbuff) 
{
	ofstream OutFile(CMDParameter);

	while (1)
	{
		ZeroMemory(recvbuff, STR_MAX_LENGTH);
		iResult = recv(Sock, recvbuff, STR_MAX_LENGTH, 0);
		if (iResult > 0)
		{
			OutFile << recvbuff;
		}
		else if (iResult == 0)
		{
			printf("Client: DataConnection closed.\n");

			break;
		}
		else
		{
			printf("Client: recv failed with error: %d\n", WSAGetLastError());

			break;
		}
	}
	OutFile.close();
	closesocket(Sock);
}

// Read the file uploaded to Server.
void ReadFile(SOCKET& Sock, char* CMDParameter, char* sendbuff) 
{
	ZeroMemory(sendbuff, STR_MAX_LENGTH);
	ifstream InFile(CMDParameter);

	while (InFile.eof() != 1) 
	{
		InFile >> sendbuff;
		iResult = send(Sock, sendbuff, strlen(sendbuff), 0);
		if (iResult == SOCKET_ERROR) 
		{
			printf("Client: send failed with error: %d.\n", WSAGetLastError());

			closesocket(Sock);
			WSACleanup();
			return;
		}
	}
	InFile.close();
	closesocket(Sock);
}

// In Passivity Mode, get Data IP and Port.
void GetDataIPAndPort(char* recvbuff, char* ServerDataIP, char* ServerDataPort) {
	int i, j;
	int count = 0;
	int Portheader, Porttailer;
	char Porthead[10];
	char Porttail[10];
	for (i = 0; recvbuff[i] != 0; i++) {
		if (recvbuff[i] == '(') {
			i++;
			break;
		}
	}
	for (j = 0; recvbuff[i + j] != 0; j++) {
		ServerDataIP[j] = recvbuff[i + j];
		if (recvbuff[i + j] == ',') {
			ServerDataIP[j] = '.';
			count++;
		}
		if (count == 4) {
			ServerDataIP[j] = 0;
			i = i + j + 1;
			break;
		}
	}
	for (j = 0; recvbuff[i + j] != 0; j++) {
		Porthead[j] = recvbuff[i + j];
		if (recvbuff[i + j] == ',') {
			Porthead[j] = 0;
			i = i + j + 1;
			break;
		}
	}
	for (j = 0; recvbuff[i + j] != 0; j++) {
		Porttail[j] = recvbuff[i + j];
		if (recvbuff[i + j] == ')') {
			Porttail[j] = 0;
			i = i + j + 1;
			break;
		}
	}
	Porttail[j] = 0;
	Portheader = atoi(Porthead);
	Porttailer = atoi(Porttail);
	itoa(Portheader * 256 + Porttailer, ServerDataPort, 10);
}
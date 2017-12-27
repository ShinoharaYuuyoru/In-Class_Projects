#undef UNICODE
#define WIN32_LEAN_AND_MEAN
#define STR_MAX_LEN 1024
#define SET_PORT "80"

#include <iostream>
#include <fstream>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

int main()
{
	printf("***** This is a simple Web Server. *****\n");

	WSADATA wsaData;
	int iResult;									// Opration result int.
	int iSendResult;								// Send result int.
	int iRecvResult;								// Receive result int.

	SOCKET ListenSocket;
	SOCKET ClientSocket;

	struct addrinfo *result = NULL;
	struct addrinfo hints;

	char sendBuffer[STR_MAX_LEN];						// Send data.
	char recvBuffer[STR_MAX_LEN];						// Receive data.
	char HTMLData[STR_MAX_LEN];
	char HTMLDataNum[STR_MAX_LEN];

	// Initial
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) 
	{
		printf("WSAStartup failed with error: %d\n", iResult);

		return 1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;						// IPv4
	hints.ai_socktype = SOCK_STREAM;				// STREAM
	hints.ai_protocol = IPPROTO_TCP;				// TCP
	hints.ai_flags = AI_PASSIVE;

	// Get address info.
	iResult = getaddrinfo(NULL, SET_PORT, &hints, &result);
	if (iResult != 0) 
	{
		printf("getaddrinfo error: %d\n", iResult);

		WSACleanup();
		return 1;
	}

	// Create a listen socket.
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) 
	{
		printf("socket error: %ld\n", WSAGetLastError());

		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}

	// Bind.
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) 
	{
		printf("bind error: %d\n", WSAGetLastError());

		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	freeaddrinfo(result);

	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) 
	{
		printf("listen error: %d\n", WSAGetLastError());

		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	// Accept a client.
	ClientSocket = accept(ListenSocket, NULL, NULL);
	if (ClientSocket == INVALID_SOCKET) 
	{
		printf("accept error: %d\n", WSAGetLastError());

		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}
	else
	{
		printf("Accepted a client.\n");
	}

	// We should shut down the listen socket to only accept one client.
	closesocket(ListenSocket);

	// Send the data to client.
	while (1)
	{
		memset(recvBuffer, 0, STR_MAX_LEN);
		int recvLength = 0;
		iRecvResult = recv(ClientSocket, recvBuffer, STR_MAX_LEN, 0);


		if (iRecvResult > 0) 
		{
			printf("%s", recvBuffer);

			strcpy(sendBuffer, "HTTP/1.1 200 OK\r\n");				// HTTP HEAD

			strcpy(HTMLData, "<html><head><title>From Socket Server</title></head><body><h1>This is my first HTML.</h1></body></html>");		// HTML
			int count = 0;
			for (count = 0;HTMLData[count] != '\0';count++);	// Response body length.
			itoa(count, HTMLDataNum, 10);						// Response body length, to string,

			strcat(sendBuffer, "Content-Type: text/html; charset=UTF-8\r\nContent-Length: ");
			strcat(sendBuffer, HTMLDataNum);
			strcat(sendBuffer, "\r\n\n");
			strcat(sendBuffer, HTMLData);

			// Send.
			iSendResult = send(ClientSocket, sendBuffer, STR_MAX_LEN, 0);
			if (iSendResult == SOCKET_ERROR) 
			{
				printf("send error: %d\n", WSAGetLastError());

				closesocket(ClientSocket);
				WSACleanup();
				return 1;
			}
			printf("sent:\n%s\n", sendBuffer);
		}
		else if (iRecvResult == 0)
		{
			printf("Connection closing...\n");

			break;
		}
		else			// Receive result Error.
		{
			printf("recv error: %d\n", WSAGetLastError());

			closesocket(ClientSocket);
			WSACleanup();
			return 1;
		}
	}

	// END.
	closesocket(ClientSocket);
	WSACleanup();

	return 0;
}
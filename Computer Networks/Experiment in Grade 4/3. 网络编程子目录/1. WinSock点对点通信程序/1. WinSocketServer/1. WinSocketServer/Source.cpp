#include <iostream>
#include <WinSock2.h>
using namespace std;

WORD wVersionRequested;
WSADATA wsaData;
int retResult;

SOCKET serverSock;
SOCKADDR_IN serverAddr;
SOCKADDR_IN clientAddr;
int addrLen = sizeof(SOCKADDR);

int main()
{
	printf("***** This is a WinSocket Server. *****\n");

	wVersionRequested = MAKEWORD(1, 1);

	retResult = WSAStartup(wVersionRequested, &wsaData);
	if (retResult != 0)
	{
		return 0;
	}
	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)
	{
		WSACleanup();
		return 0;
	}

	serverSock = socket(AF_INET, SOCK_STREAM, 0);

	serverAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(60000);

	bind(serverSock, (SOCKADDR*)&serverAddr, sizeof(SOCKADDR));

	listen(serverSock, 5);

	while (1)
	{
		SOCKET connectSock = accept(serverSock, (SOCKADDR*)&clientAddr, &addrLen);

		char sendBuffer[128];
		sprintf(sendBuffer, "Welcome %s's connection!\n", inet_ntoa(clientAddr.sin_addr));
		send(connectSock, sendBuffer, strlen(sendBuffer) + 1, 0);

		sprintf(sendBuffer, "HELLO!\n");
		send(connectSock, sendBuffer, strlen(sendBuffer) + 1, 0);

		char recvBuffer[128];
		recv(connectSock, recvBuffer, 128, 0);
		printf("%s", recvBuffer);

		closesocket(connectSock);
	}

	WSACleanup();
}
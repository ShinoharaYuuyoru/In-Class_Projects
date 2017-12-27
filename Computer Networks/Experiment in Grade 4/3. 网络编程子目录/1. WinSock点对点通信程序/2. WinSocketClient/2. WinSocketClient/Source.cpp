#include <stdio.h>
#include <WinSock2.h>

WORD wVersionRequested;
WSADATA wsaData;
int retResult;

SOCKET clientSock;
SOCKADDR_IN serverAddr;

int main()
{
	printf("***** This is a WinSocket Client. *****\n");

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

	clientSock = socket(AF_INET, SOCK_STREAM, 0);

	serverAddr.sin_addr.S_un.S_addr = inet_addr("10.51.221.173");
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(60000);

	connect(clientSock, (SOCKADDR*)&serverAddr, sizeof(SOCKADDR));

	char recvBuffer[2048];
	recv(clientSock, recvBuffer, 2048, 0);
	printf("%s", recvBuffer);

	recv(clientSock, recvBuffer, 2048, 0);
	printf("%s", recvBuffer);

	char sendStr[128] = "Please send the data.\n";
	send(clientSock, sendStr, strlen(sendStr) + 1, 0);

	closesocket(clientSock);

	WSACleanup();
}
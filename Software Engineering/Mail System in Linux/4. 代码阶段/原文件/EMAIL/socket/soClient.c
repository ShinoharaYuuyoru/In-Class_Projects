#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "variable.h"

#define SERVPORT 3333
#define MAXDATASIZE 100

void clientInit()
{
	int socketfd,recvbytes;
	//char buf[MAXDATASIZE];
	struct sockaddr_in serv_addr;
        serv_addr.sin_family=AF_INET;
        serv_addr.sin_port=htons(SERVPORT);
        serv_addr.sin_addr.s_addr=inet_addr(ip);
	bzero(&(serv_addr.sin_zero),8);
	if((socketfd=socket(AF_INET, SOCK_STREAM, 0))==-1)
	{
		perror("socket建立出错！");
		exit(1);
	}
	if(connect(socketfd,(struct sockaddr*)&serv_addr,sizeof(struct sockaddr))==-1)
	{
		perror("connect连接服务器出错！");
		exit(1);
	}
	loginInit();
	//connectdb();
	/*if(recvbytes=recv(socketfd,buf,MAXDATASIZE,0)==-1)
	{
		perror("recv接收出错！");
		exit(1);
	}
	printf("Received:%s\n",buf);*/
	close(socketfd);
}

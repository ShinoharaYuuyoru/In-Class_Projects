#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERVPORT 3333
#define BACKLOG 10

int main()
{
	int socketfd,clientfd;
	struct sockaddr_in my_addr;//主机结构体定义
	struct sockaddr_in remote_addr;//客户机结构体定义
	if((socketfd=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
		perror("socket创建出错！");
		exit(1);
	}
	my_addr.sin_family=AF_INET;
	my_addr.sin_port=htons(SERVPORT);
	my_addr.sin_addr.s_addr=inet_addr("10.10.35.43");
	bzero(&(my_addr.sin_zero),8);
	if(bind(socketfd,(struct sockaddr *)&my_addr,sizeof(struct sockaddr))==-1)
	{
		perror("bind绑定出错！");
		exit(1);
	}
	if(listen(socketfd,BACKLOG)==-1)
	{
		perror("listen监听出错！");
		exit(1);
	}
	while(1)
	{	
		if((clientfd=accept(socketfd,NULL,0))==-1)
		{
			perror("accept接受客户机请求出错！");
			continue;
		}
		printf("received a connection from %s\n",inet_ntoa(remote_addr.sin_addr));
		if(!fork())
		{	
			//printf("in\n");
			if(send(clientfd,"Hello,you are connected!\n",26,0)==-1)
			{
				perror("send出错！");
				close(clientfd);
				exit(0);
			}
			close(clientfd);
		}
	}
	return 0;
}

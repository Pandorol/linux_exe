#include<stdio.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<string.h>
#include<unistd.h>
#include <netdb.h>
#include<stdlib.h>
#include <arpa/inet.h>
#define PORT 3333
int main(int argc,char* argv[])
{
	int sockfd;
	int wrchoose=0;
	struct hostent *host;
	if(argc!=2) 
	{  /*获得命令行的第二个参数-主机名*/
		printf("Usage:%s hostname \a\n",argv[0]); 
		exit(1); 
	}
	if((host=gethostbyname(argv[1]))==NULL) 
	{  /*获得命令行的第二个参数-主机名*/ 
		fprintf(stderr,"Gethostname error\n"); 
		exit(1); 
	}
	struct sockaddr_in server_addr;                                           /*定义服务器端套接口数据结构server_addr */
	char buf[1000];
	sockfd = socket(AF_INET,SOCK_STREAM,0);                                   /* 创建套接字*/
	memset(&server_addr,'0',sizeof(struct sockaddr_in));                          /*将套接口地址数据结构清零*/	
	server_addr.sin_family=AF_INET;                                           /*设为TCP/IP地址族*/ 
	server_addr.sin_addr=*((struct in_addr *)host->h_addr);                     
	server_addr.sin_port=htons(PORT);
	server_addr.sin_port = PORT;		                                  /* 定义服务器套接字端口*/
	connect(sockfd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr));
	while(1)
	{
		printf("get connection to %s\n",inet_ntoa(server_addr.sin_addr));
		printf("write or read ? \nwrite:1\tread:2\n");
		scanf("%d",&wrchoose);
		if(wrchoose==1)
		{
			printf("please input the massage[<1000 bytes]:\n");
			scanf("%s",buf);
			send(sockfd,buf,strlen(buf),0);
			printf("send success\n");
			wrchoose=0;
		}
		if(wrchoose==2)
		{
			if(recv(sockfd,buf,1000,0)>0)
			{
				printf("received :%s\n",buf);
				wrchoose=0;
			}	
		}
	}
	close(sockfd);
	return 0;
}

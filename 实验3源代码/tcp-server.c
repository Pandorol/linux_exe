#include<stdio.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<string.h>
#include<unistd.h>
#include <netdb.h>
#include<stdlib.h>
#include <arpa/inet.h>
#define PORT 3333
int main(int argc,char * argv[])
{
	int sockfd,new_fd=0;
	int sinlen,wrchoose=0;
	struct sockaddr_in server_addr;                                           /*定义服务器端套接口数据结构server_addr */
	struct sockaddr_in client_addr;                                           /*定义客户端套接口数据结构client_addr */
	char buf[1000];
	sockfd = socket(AF_INET,SOCK_STREAM,0);                                   /* 创建套接字*/
	memset(&server_addr,'0',sizeof(struct sockaddr_in));                          /*将套接口地址数据结构清零*/
	server_addr.sin_family=AF_INET;                                           /*设为TCP/IP地址族*/ 
	server_addr.sin_addr.s_addr=htonl(INADDR_ANY);                            /*设为本机地址*/
	server_addr.sin_port=htons(PORT);
	server_addr.sin_port = PORT;		                                  /* 定义服务器套接字端口*/
	bind(sockfd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr));   /*调用bind函数绑定端口*/
	listen(sockfd,1);
	while(1)
	{
		if(!new_fd)
		{
			sinlen = sizeof(struct sockaddr_in);
			new_fd=accept(sockfd,(struct sockaddr *)(&client_addr),&sinlen);
			printf("Server get connection from %s\n",inet_ntoa(client_addr.sin_addr));
			/*TCP连接已建立，打印申请连接的客户机的IP地址*/
		}
		
		printf("write or read ? \nwrite:1\tread:2\n");
		scanf("%d",&wrchoose);
		if(wrchoose==1)
		{
			printf("please input the massage[<1000 bytes]:\n");
			scanf("%s",buf);
			send(new_fd,buf,strlen(buf),0);
			printf("send success\n");
			wrchoose=0;
		}
		if(wrchoose==2)
		{
			if(recv(new_fd,buf,1000,0)>0)
			{
				printf("received :%s\n",buf);
				wrchoose=0;
			}
		}
	}
	close(new_fd);
	close(sockfd);
	return 0;
}

#include <glade/glade.h>
#include <gtk/gtk.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<iostream>
#include<sys/socket.h>
#include<netinet/in.h>
#include <netdb.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <pthread.h>
#define PORT 8001
int sockfd,newfd[200];
int new_[200];
int tnum,exitnum=0;
struct sockaddr_in client[100];
void * thread0(void * arg)
{
	int i;
	int _num = *(int *)arg;
	printf("thread0 part \n");
	while(1)
	{
		char msg[1024]="";
		printf("readbefore and _num = %d\n",_num);
		read(newfd[_num],msg,1024);
		if(msg[0]==1)
		{
			exitnum++;
			printf("exitnum=%d\n",exitnum);
			char temp1[3]="10";
			temp1[0]=29;
			char temp0[18] = "";
			sprintf(temp0,"%d",tnum-exitnum);
			strcat(temp0,temp1);
			new_[_num]=0;
			for(i=1+exitnum;i<=tnum;i++)
			{	if(new_[i]==1)
				{
				write(newfd[i],temp0,30);
				printf("writeto %d\n",tnum);
				}
			}
			break;
		}
		printf("readafter\n");
		for(i=exitnum+1;i<=tnum;i++)
		{	if(new_[i]==1)
			{
				write(newfd[i],msg,1024);
			}
		}
	}
}
int main()
{
	int num=0;
	pthread_t id[100];
	int i;
	for(i=0;i<200;i++)
	{new_[i]=1;}
	struct sockaddr_in server;
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	memset(&server,'0',sizeof(struct sockaddr_in));
	memset(client,'0',sizeof(struct sockaddr_in)*100);
	server.sin_family=AF_INET;
	server.sin_port=htons(PORT);
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	socklen_t slen = sizeof(struct sockaddr_in);
	if(bind(sockfd , (struct sockaddr *) &server, sizeof(struct sockaddr))==-1)
	{printf("bind error\nwait  moments\n");}
	if(listen(sockfd,100))
	{printf("listen error\n");}
	while(1)
	{
		printf("accept before\n");
		num++;
		newfd[num] = accept(sockfd,(struct sockaddr *) &client[num],&slen);
		printf("accept part\n");
		char temp1[3]="10";
		temp1[0]=29;
		char temp0[18] = "";
		sprintf(temp0,"%d",num-exitnum);
		strcat(temp0,temp1);
		printf("now temp0 is %s\n",temp0);
		for(i=exitnum+1;i<=num;i++)
		{	if(new_[i]==1)
			{
				write(newfd[i],temp0,strlen(temp0));
				printf("send end\n");
			}
		}
		tnum=num;//防止主線程先行把num給+1;
		printf("before enter pthread num is %d\n",tnum);
    		pthread_create(&id[num],NULL,thread0,&tnum);
	}
	close(sockfd);
	return 0;
}

#include <glade/glade.h>
#include <gtk/gtk.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<iostream>
#include<sys/socket.h>
#include<netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#define PORT 8001
#define IP  "10.0.2.15"
using namespace std;
void on_delete_event (GtkWidget *widget,GdkEvent* event,gpointer data); 
void on_send_clicked(GtkWidget *button,gpointer userdata);
void *thread0(void *a);
GtkWidget *send_message;
GtkWidget *numberofpeople;
GtkTextBuffer *chatbox;
int sockfd,newfd;
struct sockaddr_in server;
int num =0;
int main(int argc,char* argv[])
{	
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	memset(&server,'0',sizeof(struct sockaddr_in));
	server.sin_family=AF_INET;
	server.sin_port=htons(PORT);
	server.sin_addr.s_addr = inet_addr(IP);
	if(connect(sockfd, (struct sockaddr *) &server,sizeof(server))==-1)
	{printf("connect error!\n");}
	//定義組建
	GtkBuilder      *builder;
	GtkWidget *window;
	GtkWidget *send;
	gtk_init (&argc, &argv);
	//組建從glade獲取
	builder = gtk_builder_new ();
	gtk_builder_add_from_file (builder, "chat.glade", NULL);
	window = GTK_WIDGET (gtk_builder_get_object (builder, "window1"));
	send = GTK_WIDGET (gtk_builder_get_object (builder, "button1"));
	chatbox = (GtkTextBuffer*)GTK_WIDGET (gtk_builder_get_object (builder, "Chatbox"));
	send_message = GTK_WIDGET (gtk_builder_get_object (builder, "entry1"));
	numberofpeople = GTK_WIDGET (gtk_builder_get_object (builder, "number"));
	//信號鏈接
	g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(on_delete_event),NULL); 
	g_signal_connect(G_OBJECT(send),"clicked",G_CALLBACK(on_send_clicked),NULL);
	//創建線程
	pthread_t id;
    	pthread_create(&id,NULL,thread0,NULL);
	//顯示
	gtk_widget_show_all(window);               
	gtk_main ();
	return 0;
}
void on_delete_event (GtkWidget *widget,GdkEvent* event,gpointer data) 
{
	char temp[3]="ab";
	temp[0]=1;
	write(sockfd,temp,strlen(temp));
	sleep(1);
	gtk_main_quit(); 
}
void on_send_clicked(GtkWidget *button,gpointer userdata)
{
	char msg[1024]="";
	const char *msg_ = gtk_entry_get_text(GTK_ENTRY(send_message));
	sprintf(msg,"%s",msg_);
	if(strlen(msg)==0)
	{return;}
	if(strlen(msg)>1024)
	{
		return;
	}
	if(write(sockfd,msg,strlen(msg))==-1)
	{
	printf("sendmsg error \n");
	}
	gtk_entry_set_text(GTK_ENTRY(send_message),"");
}
void *thread0(void *a)
{
	while(1)
	{
		char newmsg[1024];
		read(sockfd,newmsg,1024);
	if(strlen(newmsg)>2&&newmsg[strlen(newmsg)-2]==29)
		{
			newmsg[strlen(newmsg)-2]='\0';
	gtk_label_set_text(GTK_LABEL(numberofpeople),newmsg);
			continue;
		}
		strcat(newmsg,"\n");
		GtkTextIter start, end;
	gtk_text_buffer_get_end_iter(chatbox,&end);
	gtk_text_buffer_get_start_iter(chatbox,&start);
	gtk_text_buffer_insert(chatbox,&end,newmsg,strlen(newmsg));	
	}
}

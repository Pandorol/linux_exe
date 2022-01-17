#include<sys/sem.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
/*
struct sembuf
{
	unsigned short int sem_num;	//xin hao liang de xuhao
	short int sem_op; //  	dui xin hao liang de cao zuo
	short int sem_flg; // 	cao zuo biao shi (qian xian)
};	*/
union semun
{
	int val;
	struct semid_ds* buf;
	unsigned short * array;
	struct seminfo* _buf;
};
struct sembuf sembufinit(int a,int b)
{
	struct sembuf sembuft;
	sembuft.sem_num = a;
	sembuft.sem_op = b;
	sembuft.sem_flg = SEM_UNDO;
	return sembuft;
}
struct sembuf sembuf_p=sembufinit(0,-1);
struct sembuf sembuf_v=sembufinit(0,1);
struct date
{
	char dates[100];
};
struct Mailbox
{
	char boxname[100];                           //信箱名
	int bid;                                     //标识符
	int size;                                    //可接受消息的数目
	int mailnum,freenum,rmutex,wmutex,in,out;    //一堆信号量
	date buf[100];                               //接收的消息
};

int Mailboxinit(Mailbox* &a,char n[100],int s)/*初始化的指针和信箱名和信箱长度*/
{
	
	int shmid = shmget(0,sizeof(struct Mailbox),IPC_CREAT|0777);         //创建一个共享内存对象并返回标识符
	a = (Mailbox*)shmat(shmid,0,0777);                                   //映射
	a->size = s;                                                  
	strcpy(a->boxname,n);	
	a->mailnum= semget(0,1,IPC_CREAT|0777);                              //创建信号量
	a->freenum= semget(0,1,IPC_CREAT|0777);
	a->rmutex = semget(0,1,IPC_CREAT|0777);
	a->wmutex = semget(0,1,IPC_CREAT|0777);
	semctl(a->mailnum,0,SETVAL,0);                                       //设置信号量的值
	semctl(a->freenum,0,SETVAL,a->size);
	semctl(a->rmutex,0,SETVAL,1);
	semctl(a->wmutex,0,SETVAL,1);
	a->in = a->out = 0;
	a->bid = shmid;
	return shmid;
}

void send(Mailbox* &dest,date &mptr)
{
	semop(dest->freenum,&sembuf_p,1);                                  //p操作
	semop(dest->wmutex,&sembuf_p,1);
	strcpy(dest->buf[dest->in].dates,mptr.dates);                     //对消息进行操作     
	dest->in=(dest->in+1)%dest->size;                             
	semop(dest->wmutex,&sembuf_v,1);                                  //v操作
	semop(dest->mailnum,&sembuf_v,1);
}
void receive(Mailbox* &addr,date &mptr)
{
	semop(addr->mailnum,&sembuf_p,1);
	semop(addr->rmutex,&sembuf_p,1);
	strcpy(mptr.dates,addr->buf[addr->out].dates);
	addr->out = (addr->out+1)%addr->size;
	semop(addr->rmutex,&sembuf_v,1);
	semop(addr->freenum,&sembuf_v,1);
}

void delshm(Mailbox* &addr,int id1)
{
	shmdt((void*)addr);
	shmctl(id1,IPC_RMID,0);
}

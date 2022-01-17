#include"Mail.h"
int main()
{
	
	Mailbox *a,*b;
	int thismailid,thatmailid;
	char name[100];
	struct date mptr;
	int ismailed = 0,mailsize,items=0;
	char add[] = "  from 邮箱";
	while(1)
	{
		printf("信箱未创建,是否创建？\nyes:1\tno:0\texit:2\n");
		scanf("%d",&ismailed);
		if(ismailed==1)
		{
			printf("请输入创建信箱名\n");
			scanf("%s",name);
			printf("请输入创建信箱大小（可接收的信件数量）：\n");
			scanf("%d",&mailsize);
			thismailid = Mailboxinit(a,name,mailsize);
			printf("创建成功!\n");
			while(1)
			{
				
				printf("你的信箱id为%d\n已接受数量/可接收数量 : %d/%d\n",a->bid,a->in-a->out,a->size);
				printf("接收:1 发送:2 撤销信箱:3 刷新:其他\n");
				scanf("%d",&items);
				if(items==1)
				{
					receive(a,mptr);
					printf("接收的信息为:\n%s\n\n",mptr.dates);
				}
				else if(items==2)
				{
					while(1){
						printf("选择发送对象的邮箱id\n");
						scanf("%d",&thatmailid);
						b =(struct Mailbox*)shmat(thatmailid,0,0777);
						if(b) break;
						printf("此邮箱id不可用!\n");
						}
					printf("请输入要发送的内容:\n");
					scanf("%s",mptr.dates);
					strcat(mptr.dates,add);
					strcat(mptr.dates,a->boxname);
					send(b,mptr);
					printf("发送成功!");

				}
				else if(items==3)
				{
					delshm(a,thismailid);
					break;
				}
				else 
				{
					;
				}
			}

		}
		else if(ismailed==2)
		break;
		else continue;
	}
	return 0;
}

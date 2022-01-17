#include<stdio.h>
#include<string.h>
#include <fcntl.h>
#include<stdlib.h>
int main(int argc,char* argv[])
{
	FILE *fp;
	char msg;
	char msg2[100];
	int err;
	if(argc<=1)
	{
		printf("Usage:%s filenane\a\n",argv[0]);
		exit(1);
	}
	fp = fopen(argv[1],"at+");
	if(!fp)
	{
		printf("fail to open!Check filename\n");
		exit(1);
	}
	printf("%s content: ",argv[1]);
	err = fread(&msg,1,1,fp);
	while(err)
	{	
		printf("%c",msg);
		err = fread(&msg,1,1,fp);
	}
	while(1)
	{
	printf("\nWrite something to file %s\nor end: 0",argv[1]);
	scanf("%s",msg2);
	err = fwrite(msg2,strlen(msg2),1,fp);
	if(!err)
	{
		printf("write err!");
		exit(1);
	}
	printf("now %s content: ",argv[1]);
	fseek(fp,0,0);
	err = fread(&msg,1,1,fp);
	while(err)
	{	
		printf("%c",msg);
		err = fread(&msg,1,1,fp);
	}
	if(msg2[0]=='0')
	{
		break;
	}
	}
	fclose(fp);
	return 0;
}

#include <stdio.h>
int main()
{ 
	int i; 
	if ( fork() == 0 ) /*创建新的子进程,并判断是否是子进程*/
	{ 
		/* 子进程程序 */ 
		for ( i = 0; i < 5; i++ ) 
		{
			printf("This is child process %d \n",i);
			sleep(1); 
		}
	} 
	else 
	{ 
		/* 父进程程序*/  
		for ( i = 0; i < 5; i++ ) 
		{
			printf("This is parent process %d \n",i);
			sleep(1); 
		}
	}
}

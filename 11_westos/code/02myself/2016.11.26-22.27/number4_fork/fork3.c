# include<stdio.h>
# include<unistd.h>
int pag = 10;
int main(void)
{
	printf("begin!\n");
	pid_t pid;
	int tag = 10;
	pid = fork();
	printf("pid = %d,tag=%d,pag=%d\n",getpid(),tag,pag);
//	sleep(3);
	if(pid == 0){
		tag = 5;
		pag = 20;
		printf("pid = %d,tag=%d,pag=%d\n",getpid(),tag,pag);
		sleep(2);
		printf("子进程结束！\n");
	}
	else{
		sleep(1);
		printf("pid = %d,tag=%d,pag=%d\n",getpid(),tag,pag);
		printf("父进程结束！\n");
	}
	printf("over!\n");
	
	//sleep(3);
	return 0;
}

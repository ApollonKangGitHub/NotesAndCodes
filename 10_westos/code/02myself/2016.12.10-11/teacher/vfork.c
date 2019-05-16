#include<stdio.h>
#include<unistd.h>


int status;
int tag = 10;
int func()
{
	int a = 10;
	printf("func.....\n");
	return 0;
	exit(0);
}
int count = 0;
int main()
{
	pid_t pid;
	count++;
	printf("count=%d\n", count);
	printf("pid=%d, ppid=%d", getpid(), getppid());
	pid = vfork();
	//printf("under fork ...\n");
	if (pid>0){
		printf("only test fork code.\n");
		printf("father.....tag = %d, &tag=%p\n", tag, &tag);
		printf("pid=%d, ppid=%d", getpid(), getppid());
		//return 0;
		exit(0);
		wait(&status);
	}
	if(pid == 0){
		printf("oneline....");
		printf("pid=%d, ppid=%d", getpid(), getppid());
		func();
		tag = 100;
		printf("child.....tag = %d, &tag=%p\n", tag, &tag);
		sleep(3);
		printf("sleep over.\n");
		//_exit(3);
		return (-1);
		exit(-1);
	}
	sleep(300);
	//exit(-3);
}

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(void)
{
	pid_t pid = vfork();
	if(pid == 0){
		execl("/bin/ls","ls","-la","/home",NULL);
	}
	int status;
	wait(&status);/*加了exec后vfork的父子进程同时运行，故加wait等待*/
	printf("end\n");
	return 0;
}

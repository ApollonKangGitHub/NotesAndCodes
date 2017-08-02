#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main(void){
	pid_t pid = fork();
	if(pid == -1){
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if(pid == 0){
		printf("I'm process of child,my pid=%d,my ppid=%d,I haven't child process!\n",getpid(),getppid());
	}
	else{
		printf("I'm process of child,my pid=%d,my ppid=%d,my cpid=%d\n",getpid(),getppid(),pid);
	}
	sleep(1);
	return 0;
}

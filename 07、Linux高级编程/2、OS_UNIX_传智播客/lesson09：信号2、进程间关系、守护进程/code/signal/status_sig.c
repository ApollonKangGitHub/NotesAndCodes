#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<sys/types.h>
void sys_err(const char * ptr)
{
	perror(ptr);
	exit(EXIT_FAILURE);
}

void deal_sig(int signo)
{
	int status;
	pid_t pid;
//循环等待，可以保证回收所有子进程资源
//	while( (pid = waitpid(0, &status, WNOHANG)) > 0 ){
	pid = waitpid(0, &status, WNOHANG);
	if(WIFEXITED(status))
			printf("child %d exit and return %d\n", pid, WEXITSTATUS(status));
	else if(WIFSIGNALED(status))
			printf("child %d cancle signal %d\n", pid, WTERMSIG(status));
//	}
//	exit(EXIT_FAILURE);
}
int main(void)
{
	pid_t pid;
	int i;
	//先阻塞SIGCHLD(不用设置，SIGCHLD默认忽略)
	for(i = 0; i< 5; i++){
		if((pid = fork()) == 0)
			break;
		else if(pid < 0)
			sys_err("fork");
	}

	if(pid == 0){
			while(1){printf("I'am child of %d\n", getpid());
			sleep(10);
			}
		return i;
	}
	else if(pid > 0){
	//先注册信号，设置捕捉再解除对SIGCHLD的阻塞
		struct sigaction act;
		act.sa_handler = deal_sig;
		act.sa_flags = 0;
		sigaction(SIGCHLD, &act, NULL);
		
		while(1){
			printf("I'am parent and process id is %d\n", getpid());
			sleep(11);
		}
		while(1);
	}
	return 0;
}

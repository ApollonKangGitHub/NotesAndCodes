#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>

void accept_signal(int sig){
	printf("捕获了信号%d\n",sig);
	return;
}

int main(void)
{
	pid_t pid = fork();
	if(pid == 0){	
		signal(SIGINT,accept_signal);
		while(1);
	}
	/*系统默认父进程先执行*/
	sleep(1);/*注意：要确保子进程先执行，否则不会有效果*/
	printf("父进程给子进程%d发送信号2\n",pid);
	kill(pid,SIGINT);
	
	return 0;
}

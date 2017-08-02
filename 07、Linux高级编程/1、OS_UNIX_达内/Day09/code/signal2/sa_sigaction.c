/*
 *运行程序后重新打开终端kill发送信号
 * 键盘直接在本终端中Ctrl+c(发送信号2)被视为是进程0发送*/
#include<stdio.h>
#include<signal.h>

void accept_signal(int sig,siginfo_t * info,void *p){
	printf("进程%d发来了信号%d\n",info->si_pid,sig);
}/*该形式有更多的相关信息*/

int main(void){
	struct sigaction action = {};
	action.sa_flags = SA_SIGINFO;/*表示与accept_signal一致均调用结构体第二个成员*/
	action.sa_sigaction = accept_signal;/*设置处理函数*/
	sigaction(SIGINT,&action,NULL);
	printf("pid = %d\n",getpid());

	while(1);
	
	return 0;
}

/*
 *运行代码
 *重新打开一个终端
 *kill -sig pid给该进程发送信号测试
 *16时36分25秒--2017/1/26
 * */
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

void accept_signal(int sig){
	printf("接收到信号%d\n",sig);
}

void sig_iscom(int sig,sigset_t * pend){
	if(sigismember(pend,sig)){
		printf("信号%d来过！\n",sig);
	}
}
int main(void)
{
	signal(SIGINT,accept_signal);
	signal(SIGQUIT,accept_signal);/*2，3为不可靠信号，会丢失一部分*/
	signal(50,accept_signal);/*50为可靠信号，自行排队等待*/
	printf("pid = %d\n",getpid());
	
	printf("执行普通代码，不屏蔽信号，但是未忽略的信号会中断sleep\n");
	int ret = sleep(20);
	printf("ret = %d\n",ret);
	
	sigset_t set_new, set_old, pend;
	sigaddset(&set_new,SIGINT);	
	sigaddset(&set_new,SIGQUIT);
	sigaddset(&set_new,50);
	sigprocmask(SIG_SETMASK, &set_new, &set_old);/*设置屏蔽信号集*/
	
	printf("执行关键代码，屏蔽信号，sleep不会被屏蔽的信号中断\n");
	ret = sleep(20);
	printf("ret = %d\n",ret);
	printf("关键代码执行完毕，解除屏蔽\n");
	sigpending(&pend);
	sig_iscom(SIGINT,&pend);
	sig_iscom(SIGQUIT,&pend);
	sigprocmask(SIG_SETMASK, &set_old, NULL);/*解除屏蔽*/
	return 0;
}

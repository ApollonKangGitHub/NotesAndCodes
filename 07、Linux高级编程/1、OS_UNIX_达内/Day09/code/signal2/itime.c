#include<stdio.h>
#include<signal.h>
#include<sys/time.h>

void accept_signal(int sig){
	printf("接收了%d信号一次\n",sig);
}
int main(void)
{
	signal(SIGALRM,accept_signal);
	struct itimerval timer;
	/*1.1秒执行一次*/
	timer.it_interval.tv_sec = 1;//间隔的秒数
	timer.it_interval.tv_usec = 100000;//微秒
	/*3秒后开始*/
	timer.it_value.tv_sec = 3;
	timer.it_value.tv_usec = 0;

	setitimer(ITIMER_REAL,&timer,0);
	while(1);
}

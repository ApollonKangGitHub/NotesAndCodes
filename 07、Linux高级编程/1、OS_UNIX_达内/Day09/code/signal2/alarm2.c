#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

void accept_signal(int sig)
{
	printf("accept signal is %d\n",sig);
	alarm(2);/*循环执行*/
}
int main(void)
{
	signal(SIGALRM,accept_signal);/*自定义处理方式*/
	alarm(8);/*执行1次*/
	while(1);
}

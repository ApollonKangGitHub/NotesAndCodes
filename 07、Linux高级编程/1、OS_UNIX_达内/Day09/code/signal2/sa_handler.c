/*这里的功能signal基本都能实现
 *17:47:20--2017/1/26
 * */
#include<stdio.h>
#include<signal.h>

void accept_signal(int sig){
	printf("接收到了信号%d\n",sig);
	sleep(5);
}/*在信号处理函数执行期间，会屏蔽相同信号*/
int main(void)
{
	struct sigaction action = {};
	action.sa_handler = accept_signal;/*设置信号处理函数*/
	/*在信号处理函数执行期间，会屏蔽sa_mask设置的信号3*/
	sigemptyset(&action.sa_mask);
	sigaddset(&action.sa_mask,3);/*屏蔽信号3*/
	/*设置信号处理：第一次是自定义处理方式、调用处理函数accept_signal，之后就回复默认处理方式*/
	//action.sa_flags = SA_RESETHAND;
	/*解除了对信号处理函数执行期间对相同信号的默认屏蔽*/
	//action.sa_flags = SA_NOMASK;/*SA_NODEFER*/
	sigaction(SIGINT,&action,NULL);/*注册信号2*/

	while(1);
	return 0;
}

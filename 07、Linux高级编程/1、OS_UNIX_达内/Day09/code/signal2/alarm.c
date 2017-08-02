#include<stdio.h>
#include<signal.h>
#include<unistd.h>

int main(void)
{
	alarm(10);
	sleep(2);
	int ret_alarm = alarm(2);//取消了alarm(10)

	printf("%d\n",ret_alarm);
//	pause();
	while(1);//死循环被闹钟中断（默认的处理就是打印“闹钟”并结束进程）
	return 0;
}

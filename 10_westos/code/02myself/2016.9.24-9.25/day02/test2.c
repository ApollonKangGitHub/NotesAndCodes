# include<stdio.h>
# include<signal.h>
# include<unistd.h>
void test(int signum)
{
	if(signum == 14)
		printf("alarm sig\n");
	else if(signum == 2)
		printf("int sig");
	else
		printf("other sig");
		
}
int main (void)
{
	alarm(3);//三秒钟后提供一个信号
//	sleep(20);
	signal(SIGALRM, test);//捕获信号SIGALRM，三秒钟内没收到中断信号就一直向后执行，输出after signal 22...当三秒到时，收到alarm信号，产生中断，进入 signal函数，signal执行结束后继续回到中断处执行
	sleep(2);
	printf("after signal 22\n");
	printf("after signal 22\n");
	pause();
	alarm(3);
	signal(SIGALRM,test);
	sleep(2);
	pause();//没有信号时，就一直处于等待状态
//	printf("hello bye-bye");
	return 0;
}

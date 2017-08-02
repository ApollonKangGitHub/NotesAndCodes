/*****
**注意两种测试方式，可以看出不同缓冲区大小对执行效率的影响：
**./alarm
**./alarm > txt    -->    cat txt
*****/
#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
void deal_sig(int sig)
{
	printf("\naccept sig = %d\n",sig);
	exit(EXIT_FAILURE);
}
int main(void)
{
	int cnt = 0;
	alarm(1);
	while(1){
		cnt++;
		printf("%d\t",cnt);
		signal(SIGALRM,deal_sig);
	}
	return 0;
}

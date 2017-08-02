#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
void deal_sig(int sig){
	printf("accept sig = %d\n",sig);
	exit(EXIT_FAILURE);
}
int main(void)
{
	int cnt = 1;
	alarm(5);
	while(1){
		printf("alarm %d\n", cnt++);
		signal(SIGALRM, deal_sig);
		sleep(1);
	}
	return 0;
}

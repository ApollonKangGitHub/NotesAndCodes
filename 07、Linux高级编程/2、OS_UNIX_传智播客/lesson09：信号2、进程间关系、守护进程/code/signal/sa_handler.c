#include<stdio.h>
#include<stdlib.h>
#include<signal.h>

void deal_sig(int sig)
{
	printf("----in deal_sig----");
	printf("sig = %d\n", sig);
	sleep(2);
}

int main(void)
{
	struct sigaction act;
	act.sa_handler = deal_sig;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	
	sigaction(SIGINT, &act, NULL);
	while(1){
		printf("----int main----\n");	
		sleep(1);
	}
}

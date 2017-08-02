#include<stdio.h>
#include<signal.h>
#include<sys/types.h>
void print_sigset(const sigset_t * sig_get)
{
	int i;
	for(i=1; i<32; i++){
		if(sigismember(sig_get, i) == 1)
			putchar('1');
		else
			putchar('0');
	}
	puts("");//printf("\n");
}
int main(void)
{
	sigset_t set, get;
	printf("sizeof(sigset_t) = %d\n",sizeof(sigset_t));

	sigprocmask(SIG_BLOCK, NULL, &set);
//	sigemptyset(&set);
	sigaddset(&set, SIGINT);//可以被阻塞
	sigaddset(&set, SIGQUIT);//可以被阻塞
	sigaddset(&set, SIGKILL);//不可以被阻塞
	sigprocmask(SIG_BLOCK, &set, NULL);
	while(1){
		sigpending(&get);
		print_sigset(&get);
		sleep(1);
	}
	return 0;
}

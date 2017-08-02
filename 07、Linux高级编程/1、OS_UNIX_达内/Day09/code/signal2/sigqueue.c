#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

void accept_signal(int sig,siginfo_t * info,void * p){
	printf("进程%d发来了信号%d，附带了值为%d\n",
			info->si_pid,sig,info->si_value);
}
int main(void){
	struct sigaction action = {};
	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = accept_signal;
	//sigaction(50,&action,NULL);
	sigaction(SIGINT,&action,NULL);
	pid_t pid = fork();
	if(pid == 0){
		int i = 0;
		for(i = 0; i < 100; i++ ){
			union sigval message;
			message.sival_int = i;
		#if 0
		sigqueue(getppid(),50,message);/*可靠信号无需延时*/
		#endif
		#if 1
			sigqueue(getppid(),2,message);
			usleep(10000);
			/*由于2信号是不可靠信号，为了使100个信号完全发过去，就得延时，延时也不可太短，否则在一个信号处理的过程中，过多的不可靠信号被屏蔽而未被处理，而不可靠信号又不会去排队等待，因此丢失信号与附带信息*/
		#endif
		}
		exit(EXIT_SUCCESS);
	}
	while(1);
	return 0;
}

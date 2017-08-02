#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<signal.h>
//#include<sys/types.h>
void deal_sig(int sig, siginfo_t *message,void * ptr){
	printf("I'am %d process, I accept a signal %d and other message is %s from %d process.\n"
			,getpid(), sig,message->si_value, message->si_pid);
	exit(EXIT_FAILURE);
}

int main(void)
{
	pid_t pid = fork();
	if(pid < 0){
		perror("fork");
		exit(EXIT_FAILURE);
	}
	struct sigaction act;
	act.sa_sigaction = deal_sig;
	act.sa_flags = SA_SIGINFO;
	sigemptyset(&act.sa_mask);
	

	if(pid == 0){
		sigaction(SIGINT, &act, NULL);
		while(1){
			printf("I'am child\n");
			sleep(1);
		}
	}else{
		union sigval message;
		message.sival_ptr = "hello myson!";
		sleep(5);
		printf("I'am father %d process, I send the message of %s for my son is %d process\n"
				,getpid(), message.sival_ptr, pid);
		sigqueue(pid, SIGINT, message);
	}
}


#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<sys/sem.h>
#include<sys/ipc.h>
#include<sys/types.h>

int semid;

void error_print(const char * ptr_err){
	perror(ptr_err);
	exit(EXIT_FAILURE);
}

void accept_signal(int sig){
	semctl(semid, 0, IPC_RMID);
	exit(EXIT_SUCCESS);
}
int main(void)
{
	printf("按Ctrl + 退出!\n");
	key_t key = ftok("./",100);
	semid  = semget(key, 1, 0666|IPC_CREAT);
	if(semid == -1)
		error_print("semget");
	int res = semctl(semid, 0, SETVAL, 5);/*初始化为5*/
	if(res == -1)
		error_print("semctl");
	printf("初始化成功!\n");
	signal(SIGINT, accept_signal);
	while(1);
	return 0;
}

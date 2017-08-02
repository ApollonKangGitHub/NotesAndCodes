#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/msg.h>

void error_print(const char * ptr){
	perror(ptr);
	exit(EXIT_FAILURE);
}
int main(void)
{	
	key_t key = ftok(".",100);
	if(key == -1)
		error_print("ftok");
		
	int msgid = msgget(key, 0666|IPC_CREAT|IPC_EXCL);
	if(msgid == -1)
		error_print("msgget");

	int ret = msgsnd(msgid,"kangruojin",10,IPC_NOWAIT);
	if(ret == -1)
		error_print("msgsnd");

	printf("send ok!\n");
	return 0;
}

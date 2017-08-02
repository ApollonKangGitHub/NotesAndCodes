#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#define BUF_SIZE 20

void error_print(const char * ptr){
	perror(ptr);
	exit(EXIT_FAILURE);
}
int main(void)
{	
	key_t key = ftok(".",100);
	if(key == -1)
		error_print("ftok");
		
	int msgid = msgget(key, 0);/*获取设置为0*/
	if(msgid == -1)
		error_print("msgget");

	char buf[BUF_SIZE] = {0};
	int ret = msgrcv(msgid,buf,BUF_SIZE,0,IPC_NOWAIT);
	if(ret == -1)
		error_print("msgsnd");

	printf("recv ok!message is %s\n",buf);
	return 0;
}

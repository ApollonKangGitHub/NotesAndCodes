#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/msg.h>

struct mymsg{
	long mtype;/*类型*/
	char buf[256];/*数据*/
};

int main(void)
{
	key_t key = ftok("./",100);
	int msgid = msgget(	key, 0);
	if(msgid == -1){
		perror("msgget");
		exit(EXIT_FAILURE);
	}
	
	struct mymsg msg;
	int res = msgrcv(msgid, &msg, sizeof(msg)-sizeof(long), 2, 0);/*取2消息，当取完2后就阻塞,改成-2则取出所有小于等于类型2的数据*/
	if(res == -1){
		perror("magrecv");
		exit(EXIT_FAILURE);
	}
	printf("mtype = %ld, msg = %s\n",msg.mtype,msg.buf);
	return 0;
}

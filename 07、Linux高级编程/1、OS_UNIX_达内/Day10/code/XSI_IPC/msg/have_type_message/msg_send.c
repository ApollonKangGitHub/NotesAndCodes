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
	int msgid = msgget(	key, 0666|IPC_CREAT);/*不带IPC_EXCL，存在直接打开*/
	if(msgid == -1){
		perror("msgget");
		exit(EXIT_FAILURE);
	}

	struct mymsg msg1 = {1,"hello"};
	struct mymsg msg2 = {2,"world"};
	int res1 = msgsnd(msgid, &msg1, sizeof(msg1)-sizeof(long), 0 );
	int res2 = msgsnd(msgid, &msg2, sizeof(msg2)-sizeof(long), 0);
	
	if(res1==0 && res2==0){
		printf("send two message is ok!\n");
	}

	return 0;
}

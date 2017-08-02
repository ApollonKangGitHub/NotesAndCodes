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
int main(void)
{
	key_t key = ftok("./",100);
	int semid = semget(key, 0, 0);
	if(semid == -1)
		error_print("semget");
	int i;
	for(i=0; i<10; i++){
		pid_t pid = fork();
		if(pid == 0){
			printf("准备访问共享资源\n");
			struct sembuf op;
			op.sem_num = 0;//对应信号量下标
			op.sem_op = -1;//对因信号量-1
			op.sem_flg = 0;//阻塞

			semop(semid, &op, 1);//数组的地址(只有一个元素)与结构体地址相同
			sleep(5);
			printf("正在访问共享资源\n");
			printf("访问结束！\n");
			op.sem_op = 1;
			semop(semid, &op, 1);
			exit(EXIT_SUCCESS);
		}
	}
	return 0;
}

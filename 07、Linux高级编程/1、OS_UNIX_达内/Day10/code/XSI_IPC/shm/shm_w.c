#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/shm.h>

void error_print(const char * ptr_error){
	perror(ptr_error);
	exit(EXIT_FAILURE);
}
int main(void)
{
	key_t key = ftok("./",100);/*创建key*/
	if(key == -1)
		error_print("ftok");
	int shmid = shmget(key, sizeof(int), 0666|IPC_CREAT|IPC_EXCL);
	if(shmid == -1)
		error_print("shmget");
	int * puse = (int *)shmat(shmid, NULL, 0);/*挂接共享内存*/

	if(puse == NULL)
		error_print("shmat");
	*puse = 520;
	int ret_shmdt = shmdt(puse);
	if(ret_shmdt == -1)
		error_print("shmdt");
	
	return 0;
}

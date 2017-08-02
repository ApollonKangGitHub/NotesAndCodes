/*
 *在目录不变、项目id不变的情况下，即使ipcrm -m id删除共享内存后
 *重新编译，其key也不会变，但是id会变
 *11时35分12秒--2017/1/27
 * */
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
	key_t key = ftok(".", 100);
	if(key == -1)
		error_print("ftok");
//	key_t key = 0x640360fe;/*重新编译shm_w.c可能会变*/
	/*创建key,也可直接ipcs -m查找创建好的key，直接赋给key就不用调用ftok*/

	int shmid = shmget(key, 0, 0);/*获取id，后两个参数直接置为0即可*/
	if(shmid == -1)
		error_print("shmget");
//	int id = 688146;/*重新编译shm_w.c可能会变*/
	/*获取共享内存,shmid可以直接赋为：查找的key对应的shmid*/
		
	int * puse = (int *)shmat(shmid, NULL, 0);/*共享内存挂接*/
	if(puse == NULL)
		error_print("shmat");
	printf("shm_number:%d\n",*puse);/*共享内存使用*/

	int ret_shmdt = shmdt(puse);/*共享内存脱接*/
	if(ret_shmdt == -1)
		error_print("shmdt");

	return 0;
}

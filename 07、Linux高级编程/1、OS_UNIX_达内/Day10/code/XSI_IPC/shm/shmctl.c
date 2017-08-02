/*
 *在shm_w.c运行的前提下采用可以运行
 * */
#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>
#include<sys/ipc.h>

int main(void){
	key_t key = ftok(".",100);/*100是shm_w.c设定的项目id*/
	int shmid = shmget(key,0,0);/*只是获取*/
	if(shmid == -1){
		perror("shmget");
		exit(EXIT_FAILURE);
	}
	struct shmid_ds ds;
/*状态查询*/
	shmctl(shmid,IPC_STAT,&ds);
	printf("key=%x\n",ds.shm_perm.__key);
	printf("mode=%o\n",ds.shm_perm.mode);
	printf("size=%d\n",ds.shm_segsz);
	printf("cpid=%d\n",ds.shm_cpid);
	printf("nattch=%d\n",ds.shm_nattch);
	
/*修改状态，用ipcs -m测试修改是否成功*/
	ds.shm_perm.mode = 0640;/*只有mode可以修改*/
	ds.shm_segsz = 40;/*大小修改不会成功，但是不报错*/
	shmctl(shmid,IPC_SET,&ds);/*真正的修改，执行该函数后修改才会生效*/

/*删除共享内存*/
	shmctl(shmid,IPC_RMID,0);

	return 0;
}

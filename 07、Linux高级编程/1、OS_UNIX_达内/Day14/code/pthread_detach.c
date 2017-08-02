#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

void * task(void *p){
	int i;
	for(i=0; i<10; i++){
		printf("task:%d\n",i);
		usleep(500000);
	}
}
int main(void){
	pthread_t tid;
	pthread_create(&tid,NULL,task,NULL);
#if 1
	pthread_detach(tid);//先设定为分离状态
#endif
	pthread_join(tid, 0);//再设定为非分离状态，非分离状态无效
	
	int i;
	for(i=0; i<10; i++){
		printf("main:%d\n",i);
		usleep(500000);
	}
	return 0;
}

#include<stdio.h>
#include<pthread.h>

void * task1(void *p){
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,0);//能取消
//	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE,0);//不能取消
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,0);//立即取消
//	pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED,0);//到下一个取消点再取消
	while(1){
		printf("--**--**--\n");
		usleep(500000);
	}
}

void * task2(void *p){
	sleep(3);
	printf("取消线程task1\n");
	pthread_cancel(*(pthread_t *)p);
}

int main(void)
{
	pthread_t tid1, tid2;
	pthread_create(&tid1, NULL, task1, NULL);
	pthread_create(&tid2, NULL, task2, &tid1);

	pthread_join(tid1, NULL);
	pthread_join(tid2,NULL);

	return 0;
}

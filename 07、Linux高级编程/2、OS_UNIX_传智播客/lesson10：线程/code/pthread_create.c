#include<stdio.h>
#include<pthread.h>

void * deal_pthread(void * arg)
{
	int * p = (int *)arg;
	printf("thread ID in child thread= %x\n", pthread_self());
	printf("process ID in child thread = %d\n", getpid());
	printf("*arg = %d\n", *p);

	while(1);
}
int main(void)
{
	pthread_t tid;
	int n = 10;
	pthread_create(&tid, NULL, 	deal_pthread, (void *)&n);
	printf("thread ID in main create = %x\n", tid);
	printf("thread ID in main thread = %x\n", pthread_self());
	printf("process ID in main process = %d\n", getpid());
	
	while(1);
//	sleep(5);//与进程相似，sleep只是权宜之计，pthread_join才是长久之计
	return 0;
}

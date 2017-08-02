#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
void * thr_fn1(void * arg)
{
	printf("thread 1 returning\n");
	return (void *)1;
}
void * thr_fnr2(void * arg)
{
	printf("thread 2 returning\n");
	return (void *)2;
}
void * thr_fn3(void * arg)
{
	while(1){
		printf("thread 3 exiting\n");
		sleep(1);
	}
}
int main(void)
{
	pthread_t tid;
	void * ret;

	pthread_create(&tid, NULL, thr_fn1, NULL);
	pthread_join(tid, &ret);
	printf("thread 1 exit code %d\n", (int)ret);
	
	pthread_create(&tid, NULL, thr_fn3, NULL);
	sleep(3);
	pthread_cancel(tid);
	pthread_join(tid, &ret);
	printf("thread 3 exit code %d\n", (int)ret);
	
	return 0;
}

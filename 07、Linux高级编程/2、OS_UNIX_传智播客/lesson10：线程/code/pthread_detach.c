#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>

void *thr_fn(void *arg)
{
	int n = 3;
	while(n--){
		printf("thread count %d\n", n);
		sleep(1);
	}
	return (void *)1;
}
int main(void)
{
	pthread_t tid;
	void * ret;
	int err;

	pthread_create(&tid, NULL, thr_fn, NULL);
	//注释掉pthread_detach()与不注释分别测试
//	pthread_detach(tid);

	while(1){
		err = pthread_join(tid, &ret);
		if(err != 0){
			fprintf(stderr, "thread %s\n", strerror(err));
		}
		else{
			fprintf(stderr, "thread exit code %d\n", (int)ret);
		}
		sleep(1);
	}
	return 0;
}

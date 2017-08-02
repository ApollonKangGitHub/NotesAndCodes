#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>

void * thread_fun(void * arg)
{
	int n = 20;
	/*n>10时主线程与子线程均正常
	 *n<10时主线程成为僵尸线程<defunct>
	 *n==0时主线程与子线程均正常被回收资源
	 * */
	while(n--){
		printf("%x\t%d\n", (unsigned int)pthread_self(), n);
		sleep(1);
	}
	return (void *)1;
}
int main(void)
{
	pthread_t tid;
	pthread_attr_t attr;
	int err;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

	pthread_create(&tid, &attr, thread_fun, NULL);
	err = pthread_join(tid, NULL);
	while(1){
		if(err != 0){
			printf("%s\n",strerror(err));
			sleep(10);
			pthread_exit((void *)1);
		}
	}

	return 0;
}

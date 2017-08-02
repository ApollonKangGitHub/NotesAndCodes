
/*线程互斥量保证每个线程能够数够TIMES次
 *之后再退出循环
 * */
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

#define TIMES 5000 

int counter;

/*静态初始化互斥量*/
//pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;

pthread_mutex_t counter_mutex;
void * doit(void *);

int main(void)
{	
	/*动态初始化互斥量*/
	pthread_mutex_init(&counter_mutex, NULL);
	pthread_t tidA, tidB;

	pthread_create(&tidA, NULL, doit, NULL);
	pthread_create(&tidB, NULL, doit, NULL);

	/*wait for both threads to terminate*/
	pthread_join(tidA, NULL);
	pthread_join(tidB, NULL);
	
	/*销毁锁*/
	pthread_mutex_destroy(&counter_mutex);
	return 0;
}
void * doit(void * vptr)
{
	int i, val;
	for(i = 0; i < TIMES; i++){
	/*加锁*/
		pthread_mutex_lock(&counter_mutex);
		val = counter;
		printf("%x: %d\n",(unsigned int)pthread_self(), val + 1);
		counter = val+1;
	/*解锁*/
		pthread_mutex_unlock(&counter_mutex);
	}
	return NULL;
}

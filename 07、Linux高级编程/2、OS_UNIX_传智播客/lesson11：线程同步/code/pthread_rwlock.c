//运行后立即结束，防止产生过多数据不便观察
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<pthread.h>

int counter;
pthread_rwlock_t rwlock;

//三个线程不定时写同一个全局资源，5个线程不定时读同一个全局资源

void * thread_write(void * arg)
{
	int t;
	while(1){
		pthread_rwlock_wrlock(&rwlock);
		t = counter;
		usleep(1000);
		printf("write %x : counter=%d, ++counter=%d\n"
				,(int)pthread_self(), t, ++counter);
		pthread_rwlock_unlock(&rwlock);
		usleep(1000);
	}
}

void * thread_read(void * arg)
{
	while(1){
		pthread_rwlock_wrlock(&rwlock);
		printf("read %x : %d\n", (int)pthread_self(), counter);
		pthread_rwlock_unlock(&rwlock);
		usleep(1000);
	}
}
int main(void)
{
	int i;
	pthread_t tid[8];
	pthread_rwlock_init(&rwlock, NULL);
	for(i = 0; i < 3; i++)
		pthread_create(&tid[i], NULL, thread_write, NULL);
	for(i = 0; i < 5; i++)
		pthread_create(&tid[i], NULL, thread_read, NULL);
	for(i = 0; i < 8; i++)
		pthread_join(tid[i], NULL);
	return 0;
}

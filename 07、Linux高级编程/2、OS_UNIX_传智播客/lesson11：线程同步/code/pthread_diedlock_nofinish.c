#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<fcntl.h>

pthread_rwlock_t rwlock;

void *deal_pthread1(void *);
void *deal_pthread2(void *);
void sys_err(const char *);

int main(void)
{
	pthread_t tid1, tid2;
	pthread_rwlock_init(&rwlock, NULL);
	int ret = pthread_create(&tid1, NULL, deal_pthread1, NULL);
	if(ret > 0)
		sys_err("pthread_create tid1");

	ret = pthread_create(&tid2, NULL, deal_pthread2, NULL);
	if(ret > 0)
		sys_err("pthread_create tid2");

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	pthread_rwlock_destroy(&rwlock);
}

void *deal_pthread1(void *arg)
{
	pthread_rwlock_wrlock(&rwlock);
	int fd1 = open("test1.txt", O_RDWR);
	sleep(1);
	int fd2 = open("test2.txt", O_RDWR);

	pthread_rwlock_unlock(&rwlock);
	close(fd1);
	close(fd2);
}

void *deal_pthread2(void * arg)
{
	pthread_rwlock_wrlock(&rwlock);
	int fd2 = open("test2.txt", O_RDWR);
	sleep(1);
	int fd1 = open("test1.txt", O_RDWR);
	
	pthread_rwlock_unlock(&rwlock);
	close(fd1);
	close(fd2);
}
void sys_err(const char * err_str)
{
	fprintf(stderr, err_str);
	exit(EXIT_FAILURE);
}

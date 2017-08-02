#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>

void * thread_fun(void * arg)
{
	while(1)
		sleep(1);
}
int main(void)
{
	pthread_t tid;
	int i = 1, err;
	while(1){
		err = pthread_create(&tid, NULL, thread_fun, NULL);
		if(err != 0){
			printf("%s\n", strerror(err));
			exit(EXIT_FAILURE);
		}
		printf("num : %d\n", i++);
	}

}

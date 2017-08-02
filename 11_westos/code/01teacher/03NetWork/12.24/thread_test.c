/*gcc thread_test.c -lpthread*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define max 20

//volatile int g_tag;
int g_tag;
pthread_t tid;


void *produce(void *arg)
{
	int i ,j;
	for(i = 0; i < max; i++){
		j = g_tag;
		j = j + 1;
		usleep(10);
		g_tag = j;
	//	printf("child i = %d\tchilde =%d\n",i,g_tag);
	}
	return NULL;
}

int main(int argc, char *argv[])
{
	pthread_create(&tid, NULL, produce, NULL);
	int i;
	for(i = 0; i < max; i++) {
		g_tag = g_tag + 1;
		usleep(10);
	//	printf("father i = %d\tfather = %d\n",i,g_tag);
	}
	printf("g_tag = %d\n", g_tag);
	exit(0);
}

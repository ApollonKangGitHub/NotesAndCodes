#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

char * data[5];
int size = 0;//全局变量，存储数组下标
sem_t sem;//1
void * task(void * p){
	sem_wait(&sem);//3
	data[size] = (char *)p;//4
	sleep(1);
	size++;
	sem_post(&sem);//5
}
int main(void)
{
	sem_init(&sem, 0, 1);//2
	data[size] = "liu bei";
	size++;
	pthread_t tid1, tid2;
	pthread_create(&tid1, NULL, task, "guan yu");
	pthread_create(&tid2, NULL, task, "zhang fei");
	pthread_join(tid1,NULL);
	pthread_join(tid1,NULL);

	int i = 0;
	for(i=0; i<size; i++){
		printf("%s\n",data[i]);
	}
	sem_destroy(&sem);//6
	return 0;
}

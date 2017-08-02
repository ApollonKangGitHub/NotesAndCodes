#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

void * task(void *p){
	int i;
	for(i = 0; i < 100; i++){
		if(i == 12)
//			return (void *)i;
			pthread_exit((void *)i);//等价于return
	}
}

int main(void){
	pthread_t tid;
	pthread_create(&tid, NULL, task, NULL);
	int retval;
	pthread_join(tid, (void **)&retval);
	printf("res = %d\n",retval);
	
	return 0;
}

/*
 *pthread_create()参数的两个诡异用法
 * */
#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

void * point1(void *p){//传递的死整数，直接用不取*p也是可以的
	int pi = (int)p;
	printf("pi = %d\n",pi);
}

void * point2(void *p){
	sleep(1);//睡眠导致再使用时，p的指向已经释放
	int * pi = p;//p已经被释放(输出为0就可以验证)，不再有效，但是free()以后只是内容清空，并不回收，在解除映射之前均可以使用
	printf("*pi = %d\n",*pi);
}
int main(void)
{
	pthread_t tid1,tid2;
	int x = 100;
	pthread_create(&tid1, NULL, point1, (void *)x);
	pthread_join(tid1,NULL);

	int * p = malloc(4);
	*p = 100;	
	pthread_create(&tid2, NULL, point2, p);
	free(p);
#if 0
	int * q = malloc(4);//分配的是p的那段空间
	*q = 10;
	sleep(1);
	free(q);
#endif
	pthread_join(tid2,NULL);
	
	return 0;
}

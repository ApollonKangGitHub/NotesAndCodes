#include<stdio.h>
#include<errno.h>
#include<pthread.h>
#include<string.h>
#include<stdlib.h>
void * task(void *p){
	printf("%s\n",(char *)p);
	//p = "hello";//修改地址为只读常量区地址
	strcpy(p,"hello");//没有修改地址，原有地址在main函数中
	p = "hello";
	/*
	 *注意：第八行与第九行不能同时执行，必须注释掉一个
	 *但是当调换8、9行顺序后可以同时执行(即9、10行一起执行)
	 *这是因为"hello"在只读区
	 *p="hello"是修改p的地址，strcpy是修改p的指向的地址中的值
	 *8、9行的代码顺序试图改变只读区的值，引发段错误而退出
	 *而9、10行的顺序不会去修改只读区的值
	 * */
	//char st[] = "hello";//st指向栈区，返回的是无效的指针，不能使用
	return p;
	//return st;
}

int main(void)
{
	char str[] = "abcde";
	pthread_t tid;
	pthread_create(&tid, NULL, task, str);
	char * retval = "world";
	int ret = pthread_join(tid, (void **)&retval);
	if(ret){
		printf("pthread_join error %s\n",strerror(ret));
		exit(EXIT_FAILURE);
	}
	printf("str = %s\n",str);//str由strcpy(p,"hello");语句改变
	printf("res = %s\n",retval);//retval由p="hello";语句改变

	return 0;
}

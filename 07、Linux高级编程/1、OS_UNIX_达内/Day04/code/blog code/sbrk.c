#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#define MAX 1024
int main(void)
{
	int * p = sbrk(0);
	int * old = p;
	
	p = sbrk(MAX * MAX);
	if(p == (void *)(-1)){
		perror("sbrk");
		exit(EXIT_FAILURE);
	}
	printf("old:\t%p\np:\t%p\n",p,old);
	int * new = sbrk(0);
	printf("new:\t%p\n",new);

	printf("pid = %d\n",getpid());
//	while(1);
	sbrk(-MAX * MAX);
	p = sbrk(0);
	printf("p:\t%p\n",p);
	return 0;
}

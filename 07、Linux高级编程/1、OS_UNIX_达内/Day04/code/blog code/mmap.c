#include<stdio.h>
#include<sys/mman.h>
#include<stdlib.h>
#define MIN_LENGTH_MMAP 4096

int main (void)
{
	int * pone = (int *)mmap(NULL,MIN_LENGTH_MMAP,PROT_WRITE|PROT_READ,MAP_PRIVATE|MAP_ANONYMOUS,0,0);
	int * ptwo = malloc(MIN_LENGTH_MMAP);
	int pthree = 0;

	printf("test pid = %d\npone=%p\nptwo=%p\n&pthree=%p\n",getpid(),pone,ptwo,&pthree);

	while(1);
	munmap(pone,MIN_LENGTH_MMAP);
	free(ptwo);
	return 0;
}

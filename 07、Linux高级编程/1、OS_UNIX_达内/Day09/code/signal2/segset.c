#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

int main(void)
{
	printf("\nsize = %d\tbit = %d\n",sizeof(sigset_t),sizeof(sigset_t)*8);
	sigset_t set;
	sigfillset(&set);	printf("set fill:\tset=%u\n",set);
	sigemptyset(&set);	printf("set empty:\tset=%u\n",set);
	sigaddset(&set,2);	printf("add 2:\tset=%u\n",set);
	sigaddset(&set,3);	printf("add 3:\tset=%u\n",set);
	sigaddset(&set,10);	printf("add 1:\tset=%u\n",set);

	if(!sigismember(&set,32))
		printf("信号32不存在\n");
	sigemptyset(&set);	printf("set empty:\tset=%u\n",set);
	sigaddset(&set,32);	printf("add 32:\tset=%u\n",set);
	/*信号32~35暂时没有（没定义）,但是可以加进去*/
	if(sigismember(&set,32))
		printf("信号32存在\n\n");

	return 0;
}

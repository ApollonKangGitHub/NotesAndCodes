#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void test(int signum)
{
	printf("hello test\n");
	if(signum == 14)
		printf("alarm sig\n");
	else if(signum == 2)
		printf("int sig\n");
	else 
		printf("other sig \n");
}
int main()
{
	int i = 0;
	for(i=0; i<5; i++)
		;
	printf("before signal\n");

//	alarm(3);
	signal(SIGALRM, test);
	printf("after signal 11\n");
//	pause();


	alarm(3);
	
	signal(SIGALRM, test);
	printf("after signal 22\n");
	printf("after signal 22\n");
	printf("after signal 22\n");
	pause();

	printf("return main\n");
	return 0;
}












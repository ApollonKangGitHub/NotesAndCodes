#include <stdio.h>

static int num = 0;
int func()
{
	int ar[100][100];
	printf("%d--------func......\n",num++);
	return main();
}


int main()
{
	return func();
	printf("main end");
}


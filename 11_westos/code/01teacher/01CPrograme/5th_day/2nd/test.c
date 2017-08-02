#include <stdio.h>


int test(int a)
{
	printf("hello test\n");
}

int main()
{
//	函数指针：		
	printf("hello main \n");

	int (*pt)(int);
	pt = test;
	pt(10);

	test(10);

//	pt = test(10);


	return 0;
}




#include <stdio.h>

int test(const int a)
{
	;
}
int main()
{
	int const a = 100;
	int b = 200;
//	b = 300;
	//test(200);
	int const *pa = &b;
//	*pa = 300;
	pa = &a;
	printf("*pa: %d\n", *pa);	
	int* const pb = &a;
//	pb = &b;
	*pb = 300;
	printf("*pb: %d\n", *pb);

	return 0;
}









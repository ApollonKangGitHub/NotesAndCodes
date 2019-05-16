#include <stdio.h>

int main()
{
	int a = 100;
	int *pa = &a;
	
	printf("a %p\n", &a);
	printf("pa: %x\n", pa);


	return 0;
}

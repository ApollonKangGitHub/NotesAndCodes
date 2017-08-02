#include <stdio.h>

int main()
{
	int a = 100;
	int* pa = &a;
	int*   *ppa = &pa;

	printf("a addr %p\n", &a);
	printf("pa addr %p\n", &pa);
	printf("pa value 0x%x\n", pa);

	printf("ppa value 0x%x\n", ppa);

	printf("ppa ---> a value %d\n", **ppa);

	return 0;
}











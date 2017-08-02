#include <stdio.h>

void swap_2 (void * a, void *b, size_t size)
{
	unsigned char * p = (unsigned char *)a;//ǿ������ת��
	unsigned char * q = (unsigned char *)b;//ǿ������ת��
	unsigned char medium;

	while(size--)
	{
		medium = *p;
		*p = *q;
		*q = medium;
		p++;
		q++;
	}
	return;
}

int main(void)
{
	int a = 5, b = 12;
	printf("a=%d\tb=%d\n",a,b);
	swap_2(&a,&b,sizeof(int));
	printf("a=%d\tb=%d\n",a,b);

	return 0;
}
#include <stdio.h>

void* test(void* x, void* y)
{
	char ch = *((char*)x);
	char c = *((char*)y);

	static char d = 0;
	d = ch - c;
	return (void*)(&d);	
//	printf("ch: %c\n c: %c\n", ch, c);
}

int main()
{
	unsigned char c = 'x';	
	unsigned char d = 'y';	

	char* pc = test(&c, &d);

	printf("pc: %d\n", *pc);

	return 0;
} 

















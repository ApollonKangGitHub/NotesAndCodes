#include <stdio.h>

void* test(void* x, void* y)
{
//	unsigned char ch = *(unsigned char*)x; error

	unsigned char pc = (unsigned int)x;
	
	unsigned char ch = (unsigned char)x;
	unsigned char c = (unsigned char)y;

	printf("ch: %c\n", ch);
	printf("c: %c\n", c);
	static char d = 0;
	d = ch - c;
//	d = ch - c;
	return (void*)&d;	
}

int main()
{
	char* src = "hello world";
	char* dest = "hello";

	*src++;
	
	unsigned char c = 'x';	
	unsigned char d = 'y';	

	unsigned char* pc = (unsigned char*)test((void*)c, (void*)d);

	printf("pc: %u\n", *pc);

	return 0;
} 

















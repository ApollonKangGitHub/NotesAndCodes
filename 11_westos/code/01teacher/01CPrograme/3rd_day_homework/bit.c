#include <stdio.h>

int main()
{
	unsigned char a = 0x7e;
	unsigned char b = 0x88;

	printf("a 0x%x\n", a & ~0x88);	
	printf("b 0x%x\n", b | 0x60);	
	
}












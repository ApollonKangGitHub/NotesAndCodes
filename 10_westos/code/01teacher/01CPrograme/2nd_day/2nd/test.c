#include <stdio.h>


int a = 10;

int test(int a, char* s, char c, char* f, char e)
{
	static int a = 200;
	printf("a addr: %p\n", &a);
	printf("s addr: %p\n", &s);
	printf("c addr: %p\n", &c);
	printf("f addr: %p\n", &f);
	printf("e addr: %p\n", &e);

	printf("a: %d \n s: %s\n c: %c\n", a, s, c);
	
	char* ps = "hello";
	return 0;
}

int main()
{
	int a = 100;
	char ch = 'x';
	char* pf = "world";

	test(a, ps, ch, pf, 'y');	

	return 0;	
}









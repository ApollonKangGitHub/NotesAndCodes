#include <stdio.h>

int test(int pa, char pc, int pb, short pf , char pd, char pe,short pg)
{
	printf("pa: %p\n", &pa);
	printf("pc: %p\n", &pc);
	printf("pf: %p\n", &pf);
	printf("pb: %p\n", &pb);
	printf("pg: %p\n", &pg);

	printf("pd: %p\n", &pd);
	printf("pe: %p\n", &pe);

	return 0;
}

int main()
{
	int a = 100;
	int b = 200;
	char c = 'x';
	char d = 'y';
	short f = 2;
	short g = 4;

	test(a, c, b, f, d, 'z', g);

	return 0;
}

#include <stdio.h>
#include <string.h>

typedef int  i_int;
#define M	5

typedef struct person{
	int a;
	struct person* next;
}per;

typedef  int*     pint;
#define  p_i	int*

int main(int argc, char* argv[])
{
//	int* a, b, c;

	pint  a, b, c;
	p_i   d, e, f;
	
	int x = 100;
	int y = 200;
	int z = 300;
	
	a = &x;
	b = &y;
	c = &z;
	d = &x;
	e = y;
	f = z;	

//	i_int a = 100;
//	printf("a: %d\n", a);	
//	printf("M: %d\n", M);	

	return 0;
}

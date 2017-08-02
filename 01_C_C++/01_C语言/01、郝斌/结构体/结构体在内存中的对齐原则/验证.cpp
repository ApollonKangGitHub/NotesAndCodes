# include <stdio.h>
/*原则一*/
struct A
{
	char a;
	char b;
	char c;
	double z;
};

struct B
{
	char a;
	char b;
	char c;
	char d;
	char e;
	char f;
	double z;
};
/*原则二*/
struct C
{
	double z;
	char a;
	char b;
	char c;
	char d;
};

struct D
{
	double z;
	char a;
	char b;
	char c;
	char d;
	char e;
	char f;
	char g;	
};

int main (void)
{
	struct A a;
	struct B b;

	struct C c;
	struct D d;

	printf("%d,%d",sizeof(a),sizeof(b));
	putchar('\n');

	printf("%d,%d",sizeof(c),sizeof(d));
	putchar('\n');

	return 0;
}
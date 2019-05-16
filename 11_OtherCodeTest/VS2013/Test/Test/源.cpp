#include "stdio.h"

int add(int x, int y)
{
	return (x + y);
}
int main(int argc, char* argv[])
{
	printf("%d\n", add(10, 20));
	return 0;
}
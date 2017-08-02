#include <stdio.h>

int test(int a, char* ps)
{
	printf("a: %d\n", a);
	printf("ps: %s\n", ps);

	return 200;
}
int callback(int ca, char* ps, int (*pt)(int, char*))
{
	printf("hello callback\n");
	return pt(ca, ps);	
}
int main()
{
	printf("hello main\n");

	int ret = callback(100, "hello test", test);
	printf("ret: %d\n", ret);

	return 0;
}












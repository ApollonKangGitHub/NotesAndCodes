#include <stdio.h>

int test(int a)
{
	if(a == 1)
		return 1;
	else {
		int ret = a * test(a-1);
		
		return ret;
	}
}
int main()
{
	int a = 5;

	int ret = test(a);
	printf("ret: %d\n", ret);

	return 0;
}






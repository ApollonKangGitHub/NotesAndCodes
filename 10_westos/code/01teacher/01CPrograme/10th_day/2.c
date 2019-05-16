#include <stdio.h>

void test(char* ps)
{
	if(*ps == '\0')
		return ;
	else 		
		test(ps+1);	
	printf("%c", *ps);	
}

int main()
{
	char* str = "hello";

	test(str);

	return 0;
}






#include"error_return.h"

void print_string(char *ptr)
{
	printf("string is:%s\n",ptr);
}
char * test_string(char *ptr)
{
	if(strcmp(ptr, "error"))
		return "Success";
	else
		return "Failure";
}
int rand_test(void)
{
	srand(time(NULL));
	int num = rand()%3 + 3;
	return ((num == 5) ? -1 : num);
}
int max_int(int num1, int num2, int *max_num)
{	
	if(num1 == num2)
		return -1;
	*max_num = (num1 > num2) ? num1 : num2;
	return 0;
}


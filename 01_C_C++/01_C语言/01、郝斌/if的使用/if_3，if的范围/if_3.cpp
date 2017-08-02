# include <stdio.h>
int main (void)
{
	if (1 > 2)
		printf("aaaa\n");//为假，不输出

	printf("bbbb\n");//不属于if所控制
	return 0;
}
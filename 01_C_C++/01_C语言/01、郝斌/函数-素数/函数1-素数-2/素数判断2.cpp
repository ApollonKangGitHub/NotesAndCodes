#include <stdio.h>
int main(void)
{
	int val;
	int i;
	int j;

	printf("请输入要判断的数字:\n");
	scanf("%d", &val);

	for(i=2; i<=val; ++i)
	{
		for(j=2; j<i; ++j)
		{
			if(0 == i%j)
				break;		
		}		
			if(j == i)
				printf("%d\t",i);
	}

	return 0;
}
#include <stdio.h>
int main(void)
{
	int val;
	int i;
	int j;

	printf("������Ҫ�жϵ�����:\n");
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
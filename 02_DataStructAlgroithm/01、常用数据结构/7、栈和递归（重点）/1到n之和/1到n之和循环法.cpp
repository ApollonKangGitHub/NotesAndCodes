# include <stdio.h>

int main (void)
{
	int n,k;
	long sum = 0;
	printf("��������Ҫ������ޣ�n=:");
	scanf("%d",&n);

	for(k=1;k<=n;k++)
	{
		sum += k;
	}

	printf("1+2+...+%d= %ld\n",n,sum);
	return 0;
}

# include <stdio.h>

int main (void)
{
	int n,k;
	long mult = 1;
	printf("��������Ҫ��Ľ׳ˣ�n=:");
	scanf("%d",&n);

	for(k=1;k<=n;k++)
	{
		mult *= k;
	}

	printf("%d�Ľ׳�Ϊ��%d! = %ld\n",n,n,mult);
	return 0;
}
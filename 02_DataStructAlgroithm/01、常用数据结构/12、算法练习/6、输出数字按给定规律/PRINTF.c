# include<stdio.h>
int main (void)
{
	int n=0,i=0,j=0,ji=0,ou=0;
	printf("请输入要输出的总行数：\n");
	scanf("%d",&n);
	ou = (n%2 == 0) ? (n/2) : (n/2 + 1);
	ji = n-ou;	
	while(j<ou)
	{
		for(i=1;i<n+1;i++)
			printf("%-5d",2*j*n+i);
			printf("\n");
			j++;
	}
	j=ji;
	while(j>0)
	{
		for(i=1;i<n+1;i++)
			printf("%-5d",(2*j-1)*n+i);
		printf("\n");	
		j--;
	}
	return 0;
}
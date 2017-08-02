# include <stdio.h>
# include <stdlib.h>

int main(void)
{
	long sum1 = 1;
	long sum2 = 1;
	long t;
	int k,n;
	char ch;

	do
	{
		system("cls");

		point:printf("请直接输入您要查找的项数n(由于数据类型限制，请输入0<n<47)：\n");
		scanf("%d",&n);
		system("cls");
		if(n<=0 || n>=47)
		{
			printf("输入错误，请重新输入：\n");
			goto point;
		}
		for(k=n;k>1;k--)
		{
			sum1 = sum1+sum2;
			t = sum1;
			sum1 =sum2;
			sum2 =t;
		}
		printf("斐波那契数列第%d项为:%ld\n",n,sum1);
		printf("请问您是否继续查找？继续请按y，退出请按n:\n");
		scanf(" %c",&ch);

	}while(ch == 'y' || ch == 'Y');

	
	return 0;
}
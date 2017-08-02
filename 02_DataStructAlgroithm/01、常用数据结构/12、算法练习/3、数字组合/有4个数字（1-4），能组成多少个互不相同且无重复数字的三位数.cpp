/*
	2016年4月29日21:45:17
	有1、2、3、4个数字，能组成多少个互不相同且无重复数字的三位数？都是多少？
*/
# include <stdio.h>
int main(void) 
{ 

	int i,j,k,num=0; 

	printf("所有的结果：\n"); 

	/*以下为三重循环*/ 
	for(i=1;i<6;i++)
	{
		for(j=1;j<6;j++)
		{
			for (k=1;k<6;k++) 
			{ 
				if (i!=k&&i!=j&&j!=k) 	/*确保i、j、k三位互不相同*/ 
				{
					printf("%-5d",100*i+10*j+k); 
					num++;
				}
			} 
		}
		putchar('\n');
	}
	putchar('\n');
	printf("num=%d\n",num);
	return 0;
} 


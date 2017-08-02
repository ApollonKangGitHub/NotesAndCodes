/*
	2016年4月28日11:57:03
	数组中的偶数全部放在奇数的后边

	从第一个开始，执行第i个时，i-1及之前的问题已经解决，不会出现死循环。
*/
# include <stdio.h>
int main (void)
{
	int aim[11]={120,13,10,19,25,14,39,36,37,99,102,};
	int i = 0;
	int j = 0;
	int temp;

	for (i=1; i<11; i++)
	{
		if (aim[i]%2 != 0)
		{
			 temp = aim[i];
			 for (j=i; j>0; j--)
				 aim[j] = aim[j-1];
			 aim[0] = temp;
		}
	}
	for (i=0; i<11; i++)
		printf("%d  ",aim[i]);

	return 0;
}

/*
	2016年2月2日14:06:03
	求：
	1到100之间的所有奇数之和，奇数个数，奇数平均值；
	1到100之间的所有偶数之和，偶数个数，偶数平均值
*/

# include <stdio.h>
int main (void)
{
	int i;
	int j = 0;
	int k = 0;
	int sum1 = 0;
	int sum2 = 0;
	int avg1, avg2;

	for (i=1;i<=100;++i)
	{
		if (i%2 != 0)
		{
			sum1 +=i;
			j++;
		}else
		{
			sum2 +=i;
			k++;
		}
	} 

	avg1 = sum1 / j;
	avg2 = sum2 / k;

	printf("1到100之间的所有奇数之和sum1=%d\n",sum1);
	printf("奇数的个数为%d\n",j);
	printf("奇数的平均数为avg1=%d\n",avg1);
	printf("1到100之间的所有偶数之和sum2=%d\n",sum2);
	printf("偶数的个数为%d\n",k);
	printf("偶数的平均数为avg2=%d\n",avg2);

	return 0;

}
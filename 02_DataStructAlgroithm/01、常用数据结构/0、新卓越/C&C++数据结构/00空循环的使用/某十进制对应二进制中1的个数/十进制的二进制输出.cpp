/*
	2016年6月3日14:25:36
	十进制转成任意n进制并输出与转换成二进制并输出都类似
*/
# include <stdio.h>
int main (void)
{
	unsigned long number;
	printf("Please input your number of decimal system:\n");
	scanf("%u",&number);
	int cnt=0;

	printf("十进制数%u的二进制数为:\n",number);
	while(number>0)
	{
		if(number % 2 != 0)
		{
			putchar('1');
			cnt++;
		}
		else
			putchar('0');
		number = number/2;
	}

	return 0;
}
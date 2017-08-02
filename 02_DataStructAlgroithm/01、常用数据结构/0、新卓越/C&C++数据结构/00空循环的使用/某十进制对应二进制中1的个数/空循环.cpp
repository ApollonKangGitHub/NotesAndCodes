/*
	2016年6月3日14:14:38
	判断某十进制数对应二进制中1的个数
*/
# include <stdio.h>
int main (void)
{
	unsigned long number;
	printf("Please input your number of decimal system:\n");
	scanf("%u",&number);
	unsigned long point = number;

	for(int cnt = 0; number>0 && (number%2==0 || cnt++); number=number/2);
	printf("十进制%u对应二进制中'1'的个数为：%d\n",point,cnt);
	return 0;
}
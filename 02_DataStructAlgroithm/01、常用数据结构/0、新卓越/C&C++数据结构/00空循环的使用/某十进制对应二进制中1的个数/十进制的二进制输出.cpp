/*
	2016��6��3��14:25:36
	ʮ����ת������n���Ʋ������ת���ɶ����Ʋ����������
*/
# include <stdio.h>
int main (void)
{
	unsigned long number;
	printf("Please input your number of decimal system:\n");
	scanf("%u",&number);
	int cnt=0;

	printf("ʮ������%u�Ķ�������Ϊ:\n",number);
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
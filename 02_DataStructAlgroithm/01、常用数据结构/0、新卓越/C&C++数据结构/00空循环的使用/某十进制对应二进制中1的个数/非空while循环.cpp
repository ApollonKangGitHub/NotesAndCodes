# include <stdio.h>
int main (void)
{
	unsigned long number;
	printf("Please input your number of decimal system:\n");
	scanf("%u",&number);
	int cnt=0;
	unsigned long point = number;

	while(number>0)
	{
		if(number % 2 != 0)
			cnt ++;
		number = number/2;
	}

	printf("ʮ����%u��Ӧ��������'1'�ĸ���Ϊ��%d\n",point,cnt);
	return 0;
}
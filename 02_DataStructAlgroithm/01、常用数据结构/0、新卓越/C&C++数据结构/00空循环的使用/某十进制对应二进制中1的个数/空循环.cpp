/*
	2016��6��3��14:14:38
	�ж�ĳʮ��������Ӧ��������1�ĸ���
*/
# include <stdio.h>
int main (void)
{
	unsigned long number;
	printf("Please input your number of decimal system:\n");
	scanf("%u",&number);
	unsigned long point = number;

	for(int cnt = 0; number>0 && (number%2==0 || cnt++); number=number/2);
	printf("ʮ����%u��Ӧ��������'1'�ĸ���Ϊ��%d\n",point,cnt);
	return 0;
}
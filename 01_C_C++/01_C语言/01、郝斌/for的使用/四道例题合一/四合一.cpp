/*
	2016��2��2��14:06:03
	��
	1��100֮�����������֮�ͣ���������������ƽ��ֵ��
	1��100֮�������ż��֮�ͣ�ż��������ż��ƽ��ֵ
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

	printf("1��100֮�����������֮��sum1=%d\n",sum1);
	printf("�����ĸ���Ϊ%d\n",j);
	printf("������ƽ����Ϊavg1=%d\n",avg1);
	printf("1��100֮�������ż��֮��sum2=%d\n",sum2);
	printf("ż���ĸ���Ϊ%d\n",k);
	printf("ż����ƽ����Ϊavg2=%d\n",avg2);

	return 0;

}
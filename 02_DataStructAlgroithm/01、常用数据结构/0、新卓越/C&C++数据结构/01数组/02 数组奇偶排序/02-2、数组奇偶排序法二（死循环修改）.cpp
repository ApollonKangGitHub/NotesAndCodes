/*
	2016��5��26��22:15:53
*/
# include <stdio.h>
void sort(int *,int);
int main (void)
{
	int a[8] ={3,2,4,8,5,7,6,9};
	sort(a, 8);

	for(int i=0;i<8;i++)
		printf("%-4d",a[i]);
	
	putchar('\n');
	return 0;
}

void sort(int * a, int len)
{
	int i, j, temp, point;
	i = 0;
	point = len-1;

	while(i < point)
	{
		if(a[i] % 2 != 0)
			i ++;
		else
		{
			temp = a[i];
			for(j = i; j < point; j++)
				a[j] = a[j+1];
			a[j] = temp;
			point --;
			//ÿ��ż�����Ųһ�Σ�point��ǰŲһ�Σ���point����ߵ�Ԫ�ض��Ѿ���ż�����ȱ������ظ��ƶ����ֽ���ѭ������
		}
	}
}
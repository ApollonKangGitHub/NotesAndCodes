
/*
	2016��4��28��21:03:17
	���Ŵ���
*/
# include <stdio.h>

void move_element(int * a, int s, int e)
{
	int i, j, temp;

	for(i=s,j=e;i<j;i++,j--)
	{
		temp = a[i];
		a[i] = a[j];
		a[j] = temp;
	}

	return;
}
int main (void)
{
	int i = 0;
	int a[8]={10,20,30,40,50,60,70,80};

	move_element(a,0,7);
	move_element(a,0,4);//������
	move_element(a,5,7);

	for(i=0; i<8; i++)
	{
		printf("%-5d",a[i]);
	}
	putchar('\n');

	return 0;
}//�������ݼ��ϵ��ƶ��㷨������ͨ���˷ѿռ��������
//��д�㷨�������˷ѿռ�Ϊǰ��

/*
	2016��3��17��18:04:59
	ð������
*/
# include <stdio.h>

void pai(int a[],int len)//int a[]��int * a������
{
	int i, j, t;
	for(i=0; i<len-1; i++)//����i<len����ȷ��i<len-1
	{
		for(j=0; j<len-1-i; j++)//ע��˴����ж������i��ͬ����ͬ������Ϊj<len-1-i
		{
			if(a[j] > a[j+1])
			{
				t = a[j];
				a[j] = a[j+1];
				a[j+1] = t;
			}
		}
	}
}
int main(void)
{
	int a[8];
	int i;
	printf("��������Ҫ����İ˸����֣�\n");
	for(i=0; i<8; i++)
	{
		scanf("%d,",&a[i]);
	}

	pai(a,8);
	for(i=0;i<8;i++)//��һ�ε��Դ��󣬸þ����˲��üӵķֺ�
	{
		printf("%-4d",a[i]);
	}
	printf("\n");

	return 0;
}
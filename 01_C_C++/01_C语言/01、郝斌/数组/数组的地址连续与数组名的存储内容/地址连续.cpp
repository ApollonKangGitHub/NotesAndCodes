/*
	2016��3��11��14:57:00
	>>һλ�������洢����
	>>����������
*/
#include<stdio.h>
int main(void)
{
	int add[8];
	int i,j,k;
	int blue[3][4];

	for (i=0; i<8; i++)
	{
		if(i%3==0)
		{
			printf("\n");
		}
		printf("add[%d]��ַΪ%#X\t",i,&add[i]);
	}
	printf("\n\nadd��ֵΪ%#X������add[0]�ĵ�ַ\n����add��һ�����һά�����һλԪ�ص�ַ��ָ�����",add);

	for (j=0; j<3; j++)
	{
		printf("\n\n");
		for (k=0; k<4; k++)
		{
			if(k%2==0)
			{
				printf("\n");
			}
			printf("blue[%d][%d]��ַΪ%#X\t",j,k,&blue[j][k]);
		}
	}
	printf("\n%#X",blue);
	printf("\n\nblue��ֵΪ%#X������blue[0][0]�ĵ�ַ\n����blue��һ����Ŷ�ά�����һλԪ�ص�ַ��ָ�����",blue);

	printf("\n");

	return 0;
}
/*
	2016��3��11��16:03:03
	���addΪһά��������
	add[i]��Զ����*(p+i)
*/
#include<stdio.h>
int main(void)
{
	int add[8]={25,2,3,65,4,78,96,54};
	int i,j,k;
	int m = 0;
	int blue[3][4]={
						{21,22,23,29},
						{15,16,17,18},
						{12,25,36,24}
					};

	for (i=0; i<8; i++)
	{
		printf("add[%d]=%d\t*(add+%d)=%d\n",i,add[i],i,*(add+i)); 
	}
	printf("\n���ۣ�add[i]��Զ����*(p+i)\n\n\n");

/*	for (j=0; j<3; j++)
	{
		for (k=0; k<4; k++)
		{
			m ++;
			printf("blue[%d][%d]=%d\t *(blue+%d)=%d\n",j,k,blue[j][k],m,*(blue+m)); 

		}
	}
	printf("\n���ۣ�blue[j][k]��Զ����*(blue+(4*j+k))\n\n");
	//����������Ԥ����
	//��ά�����൱��Ԫ����һά�����һλ���飬
	//���Բ�����Ϊ"add[i]��Զ����*(p+i)"�����������ڶ�ά���顣
*/

	return 0;
}
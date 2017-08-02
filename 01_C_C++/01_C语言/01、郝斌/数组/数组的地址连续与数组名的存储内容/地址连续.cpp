/*
	2016年3月11日14:57:00
	>>一位数组名存储内容
	>>数组连续性
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
		printf("add[%d]地址为%#X\t",i,&add[i]);
	}
	printf("\n\nadd的值为%#X，等于add[0]的地址\n表明add是一个存放一维数组第一位元素地址的指针变量",add);

	for (j=0; j<3; j++)
	{
		printf("\n\n");
		for (k=0; k<4; k++)
		{
			if(k%2==0)
			{
				printf("\n");
			}
			printf("blue[%d][%d]地址为%#X\t",j,k,&blue[j][k]);
		}
	}
	printf("\n%#X",blue);
	printf("\n\nblue的值为%#X，等于blue[0][0]的地址\n表明blue是一个存放二维数组第一位元素地址的指针变量",blue);

	printf("\n");

	return 0;
}
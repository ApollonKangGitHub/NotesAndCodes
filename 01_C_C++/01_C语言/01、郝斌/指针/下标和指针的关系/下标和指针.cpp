/*
	2016年3月11日16:03:03
	如果add为一维数组名则
	add[i]永远等于*(p+i)
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
	printf("\n结论：add[i]永远等于*(p+i)\n\n\n");

/*	for (j=0; j<3; j++)
	{
		for (k=0; k<4; k++)
		{
			m ++;
			printf("blue[%d][%d]=%d\t *(blue+%d)=%d\n",j,k,blue[j][k],m,*(blue+m)); 

		}
	}
	printf("\n结论：blue[j][k]永远等于*(blue+(4*j+k))\n\n");
	//输出结果不是预想结果
	//二维数组相当于元素是一维数组的一位数组，
	//所以不能认为"add[i]永远等于*(p+i)"该理论适用于二维数组。
*/

	return 0;
}
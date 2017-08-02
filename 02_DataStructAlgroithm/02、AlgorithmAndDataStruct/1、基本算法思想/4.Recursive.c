/*
 *Name:recursive algorithm 
 *Time:2017年4月21日15:29:50
 *Author:KangRuoJin
 *Mail:mailbox_krj@163.com
*/

/*
 *Example 1:求阶乘
 *凡是用递归可以做出来的，用循环一定可以做出来
*/
#include<stdio.h>
#include<stdlib.h>
unsigned int CalcRecursive(unsigned int max)
{
	if(max <= 1)
		return max;
	else
		return CalcRecursive(max-1)*max;
}

void OrderMultiplicaion(void)
{
	unsigned int max, result, i;
	printf("请输入要求的阶乘值：\b");
	scanf("%d",&max);
	result = CalcRecursive(max);
	for(i=1;i<max;i++)
		printf("%d*",i);
	printf("%d=%u\n",max,result);
}
/*
 *Example 2:十进制到二进制/八进制/十六进制的转换
*/
char bit[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
void ConversionRecursive(int num,int hex)
{
	int print;
	print = num % hex;
	if(num >= hex){
		num /= hex;
		ConversionRecursive(num,hex);
	}
	printf("%c",bit[print]);
}
void HexadecimalConversion(void)
{
	int hex, num;
	printf("请输入要转换的十进制数字:");
	scanf("%d",&num);
	printf("请输入要转化至的进制类型(2~16):");
	scanf("%d",&hex);
	if(hex > 16 || hex < 2){
		printf("error\n");
		exit(-1);
	}
	ConversionRecursive(num,hex);
	printf("\n");
}
int main(void)
{
	OrderMultiplicaion();	
	HexadecimalConversion();
	return 0;
}
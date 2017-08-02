# include <stdio.h>
# include <stdlib.h>
int main (void)
{
	char ch;

	do
	{
		system("cls");
		system("color 0A");

		int i,j,k;

		printf("请输入要进行位运算的两个数字（i，j）：\n");
		scanf("%d,%d",&i,&j);

		k = i & j;//按位与
		printf("%d\n",k);

		k = i | j;//按位或

		printf("%d\n",k);//注意当按位运算时如果反码第一位为1（表明该数为负数！！），则其值为负需要取反加1之后取相反数。

		k = i ^ j;//按位异或
		printf("%d\n",k);

		k = ~ j;//按位取反
		printf("%d\n",k);

		printf("是否继续：（Y/N）:");
		scanf(" %c",&ch);

	}while('Y' == ch || 'y'==ch);

	return 0;
}
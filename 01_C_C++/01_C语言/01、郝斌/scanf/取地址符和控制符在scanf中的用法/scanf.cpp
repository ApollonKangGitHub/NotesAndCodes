# include <stdio.h>
int main(void)
{
	int i;

	scanf("%d",&i);
	printf("%d,%o,%X,%#X\n",i,i,i,i);

	return 0;
}
/*
输出结果为：
	220
220,334,DC,0XDC
*/

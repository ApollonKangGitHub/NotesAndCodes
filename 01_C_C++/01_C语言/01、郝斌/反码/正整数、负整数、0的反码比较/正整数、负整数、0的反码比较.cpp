/*
	0以%#X输出时为0与0X00000000是等效的。
*/
# include <stdio.h>
int main (void)
{
	int i = -45;
	int j = 45;
	int k = -0;
	int m = 0;
	printf("%d\t%#X\n",i,i);
	printf("%d\t%#X\n",j,j);
	printf("%d\t%#X\n",k,k);
	printf("%d\t%#X\n",m,m);

	return 0;

}
# include <stdio.h>

int main (void)

{
	int i;
	int j;
	int t;//临时变量一般用t

	printf("please input (i=_ ,j=_ ):");
	scanf("i=%d,j=%d",&i,&j);

	t = i;
	i = j;
	j = t;

	printf("i=%d\n",i);
	printf("j=%d\n",j);

	return 0;
}
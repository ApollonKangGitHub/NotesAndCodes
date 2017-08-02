# include <stdio.h>

int main (void)

{
	int a, b, c;

	printf("please input three numbers (a,b,c):");
	scanf("%d,%d,%d",&a, &b, &c);

	if (a > b && a > c && b > c)
		printf("%d,%d,%d\n",a,b,c);

	if (a > b && a > c && b < c)
		printf("%d,%d,%d\n",a,c,b);

	if (b > a && b > c && a > c)
		printf("%d,%d,%d\n",b,a,c);

	if (b > a && b > c && a < c)
		printf("%d,%d,%d\n",b,c,a);

	if (c > a && c > b && a > b)
		printf("%d,%d,%d\n",c,a,b);

	if (c > a && c > b && a < b)
		printf("%d,%d,%d\n",c,b,a);


	return 0;
}
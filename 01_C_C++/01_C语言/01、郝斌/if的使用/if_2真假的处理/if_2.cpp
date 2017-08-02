# include <stdio.h>
int main (void)
{
	int i,j,k;
	printf("Please input three numbers (i,j,k):\n");
	scanf("%d,%d,%d",&i,&j,&k);

	if (i)
		printf("AAAAAA\n");   //i!=0为真，输出；i==0为假，不输出
	if (j)
		printf("BBBBBB\n");  //j==0为假，不输出；j!=0为真，输出

	if (k == 0)
		printf("CCCCCC\n");  
	if (k != 0)
		printf("DDDDDD\n");    //k=0为真，输出；k!=0为假不输出
	return 0;
}
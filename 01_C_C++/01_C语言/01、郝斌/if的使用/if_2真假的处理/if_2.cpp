# include <stdio.h>
int main (void)
{
	int i,j,k;
	printf("Please input three numbers (i,j,k):\n");
	scanf("%d,%d,%d",&i,&j,&k);

	if (i)
		printf("AAAAAA\n");   //i!=0Ϊ�棬�����i==0Ϊ�٣������
	if (j)
		printf("BBBBBB\n");  //j==0Ϊ�٣��������j!=0Ϊ�棬���

	if (k == 0)
		printf("CCCCCC\n");  
	if (k != 0)
		printf("DDDDDD\n");    //k=0Ϊ�棬�����k!=0Ϊ�ٲ����
	return 0;
}
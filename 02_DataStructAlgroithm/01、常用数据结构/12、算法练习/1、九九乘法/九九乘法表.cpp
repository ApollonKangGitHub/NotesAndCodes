# include <stdio.h>
# include <stdlib.h>
# include <conio.h>

int main(void)
{
	system("color 0A");

	int i,j,k;
	printf("�žų˷���\n");

	for(i=1;i<=9;i++)
	{
		for(j=1;j<=i;j++)
		{
			k = i*j;
			printf("%d*%d=%d\t",j,i,k);
		}
		printf("\n");
	}

	getch();
	return 0;
}
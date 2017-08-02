# include <stdio.h>
void move_element(int * a,int n);
int main (void)
{
	int i = 0;
	int a[8]={10,20,30,40,50,60,70,80};
	move_element(a,8);

	for(i=0; i<8; i++)
	{
		printf("%d  ",a[i]);
	}
	putchar('\n');

	return 0;
}

void move_element(int a[],int n)
{
	int i,j,t;

	//时间复杂度高，不好
	for(i=0; i<3; i++)
	{
		t = a[0];
		for(j=0; j<n-1; j++)
		{
			a[j]=a[j+1];
		}
		a[j]=t;
	}
}
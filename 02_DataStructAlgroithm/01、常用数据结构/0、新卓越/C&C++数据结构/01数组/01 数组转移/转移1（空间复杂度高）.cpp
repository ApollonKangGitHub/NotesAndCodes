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
	//�ռ临�Ӷȸߣ�����
	int b[100];

	for(i=3,j=0; i<n; i++,j++)
		 b[j]=a[i];

	for(i=0; j<n; i++,j++)
		b[j] = a[i];

	for(i=0; i<n; i++)
		a[i] = b[i];

}
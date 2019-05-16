# include<stdio.h>

void Sort(int *a,int len);
void Print(int *a,int len);
int main (void)
{
	int a[11]={3,7,-3,-5,2,1,0,9,21,18,5};

	Print(a,11);
	Sort(a,11);
	Print(a,11);

	return 0;
}
void Print(int *a,int len)
{
	int i=0;
	for(i=0;i<len;++i)
	{
		printf("%d  ",a[i]);
	}
	printf("\n");
}
void Sort(int *a,int len)
{
	int i,j,k,temp;
	for(i=1;i<len;++i)
	{
		temp = a[i];
		for(j=0;j<i && (a[j]<temp);++j);
		if(i>j)	
		{
			for(k=i;k>j;--k)
			{
				a[k]=a[k-1];
			}	
			a[j] = temp;
		}
	}
}

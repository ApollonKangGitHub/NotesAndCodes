# include<stdio.h>

void Print(int *a,int len);
void Sort(int *a,int len);

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
	int i,j,temp;
	int *pmin;
	for(i=0;i<len;++i)
	{	
		temp = a[i];
		pmin = &a[i];
		for(j=i+1;j<len;++j)
		{
			if(a[j]<*pmin)
				pmin=&a[j];
		}
		a[i] = *pmin;
		*pmin = temp;	
	}
}

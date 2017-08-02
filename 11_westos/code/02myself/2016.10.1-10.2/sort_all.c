# include<stdio.h>

void Print(int *a,int len);
void Sort_insert(int *a,int len);
void Sort_choose(int *a,int len);

int main (void)
{
	int a[11]={3,7,-3,-5,2,1,0,9,21,18,5};
	int b[12]={2,11,7,9,8,-4,3,2,10,0,-5,3};
	printf("插入排序：\n");
	Print(a,11);
	Sort_insert(a,11);
	Print(a,11);
	
	printf("选择排序：\n");
	Print(b,11);
	Sort_insert(b,11);
	Print(b,11);

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
void Sort_choose(int *a,int len)
{
	int i,j,temp;
	int *pmin;
	for(i=0;i<len;++i)
	{	
		temp = a[i];
		pmin = &a[i];
		for(j=i+1;j<len;++j)
			if(a[j]<*pmin)
				pmin=&a[j];
		a[i] = *pmin;
		*pmin = temp;	
	}
}
void Sort_insert(int *a,int len)
{
	int i,j,k,temp;
	for(i=1;i<len;++i)
	{
		temp = a[i];
		for(j=0;j<i && (a[j]<temp);++j);
		if(i>j)	
		{
			for(k=i;k>j;--k)
				a[k]=a[k-1];	
			a[j] = temp;
		}
	}
}

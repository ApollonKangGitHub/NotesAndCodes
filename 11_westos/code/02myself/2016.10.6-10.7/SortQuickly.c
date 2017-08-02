# include<stdio.h>

void QuicklySort(int *a,int low, int high);
int FindPos(int *a,int low,int high);
void Print(int *a,int len);

int main(void)
{
	int a[20]={12,19,-3,-8,4,2,5,1,9,7,-5,13,-2,8,22,-24,3,6,7,39};
	printf("排序之前:\n");
	Print(a,20);
	QuicklySort(a,0,20);
	printf("排序之后：\n");
	Print(a,20);
	return 0;
}

void Print(int *a,int len)
{
	int i;
	for(i=0;i<len;++i)
		printf("%d  ",a[i]);
	printf("\n");
}

void QuicklySort(int *a,int low, int high)
{
	int pos;
	if(low < high)
	{
		pos = FindPos(a,low,high);
		QuicklySort(a,low,pos-1);
		QuicklySort(a,pos+1,high);
	}
}

int FindPos(int *a,int low,int high)
{
	int key = a[low];
	while(low < high)
	{
		while(low < high && (a[high] >= key))
			high--;
		a[low] = a[high];

		while(low < high && (a[low] <= key))
			low++;
		a[high] = a[low];
	}//结束时，high和low相等
	a[low] = key;	//a[high] = key;
	return low;
}
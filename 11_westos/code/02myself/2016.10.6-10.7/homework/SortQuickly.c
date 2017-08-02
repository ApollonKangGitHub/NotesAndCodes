# include<stdio.h>

void QuicklySort(int *a,int low, int high);//递归排序函数
int FindFlag(int *a,int low,int high);//flag前不比flag大，flag后都不比flag小，找到flag位置
void Print(int *a,int len);//遍历输出

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
	int flag;
	if(low < high)//外部循环终止条件
	{
		flag = FindFlag(a,low,high);
		QuicklySort(a,low,flag-1);//flag左侧递归
		QuicklySort(a,flag+1,high);//flag右侧递归
	}
}

int FindFlag(int *a,int low,int high)
{
	int key = a[low];
	while(low < high)//内部循环终止条件
	{
		while(low < high && (a[high] >= key))//该处low<high不可少，因为每进一次循环high都会改变
			high--;
		a[low] = a[high];

		while(low < high && (a[low] <= key))//该处low<high不可少，因为每进一次循环low都会改变
			low++;
		a[high] = a[low];
	}//After,high == low
	a[low] = key;	//a[high] = key;
	return low;		//return high;
}
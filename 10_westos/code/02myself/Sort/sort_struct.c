# include<stdio.h>
# include<stdlib.h>
# include<time.h>

struct Sort_Arr{
	int * arr;
	void (*print_arr)(int *,int);//遍历
	void (*sort_bubble)(int *,int);//冒泡排序
	void (*sort_insert)(int *, int);//插入排序
	void (*sort_choose)(int *, int);//选择排序
	void (*sort_quickly)(int *, int, int);//快速排序
	int (*find_pos)(int *, int, int);//快排找pos
	int * (*rand_arr)(int);//生成随机数数组
};


void Print(int *a,int len)
{
	if(0 == len)
	{
		printf("数组为空！\n");
		return;
	}
	int i=0;
	for(i=0;i<len;++i)
		printf("%d  ",a[i]);
	printf("\n");
}

void SortBubble(int *a,int len)
{
	int i, j, temp;
	for(i=0;i<len;i++)
		for(j=0;j<len-i-1;j++)
			if(a[j] > a[j+1])
			{
				temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
			}
}
void SortChoose(int *a,int len)
{
	int i,j,temp,min;
	
	for(i=0;i<len;i++){
		min = a[i];
		tmp = i;
		for(j=i+1; j<len; j++){
			if(a[j] < min){
				min = a[j];
				tmp = j;
			}
		}
		if(tmp != i){
			a[tmp] = a[i];
			a[i] = min;
		}
	}
}
void SortInsert(int *a,int len)
{
	int i,j,k,temp;
	for(i=1;i<len;++i)
	{
		temp = a[i];
		j = i-1;
		while(j >= 0 && a[j] > temp){
			a[j+1] = a[j];//后移
			j--;
		}
		a[j+1] = temp;
	}
}
	
void SortQuickly(int *a, int low, int high)
{
	int pos;
	if(low < high)
	{
		pos = FindPos(a, low, high);
		SortQuickly(a, low, pos-1);
		SortQuickly(a, pos+1, high);
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
	}
	a[low] = key;
	return low;
}
int * RandArr(int n)
{
	int i;
	int * a = (int *)malloc(sizeof(int) * n);
	if(NULL == a)
	{
		printf("内存分配失败导致数组创建失败！");
		exit(EXIT_FAILURE);	
	}
	srand(time(NULL));
	for(i=0; i<n; i++)
		a[i] = rand()%51-25;//生成-25～45之间的随机数数组		
	return a;
}
int main (void)
{	
	struct Sort_Arr SORTARR = { 
		.print_arr = Print,
		.sort_bubble = SortBubble,
		.sort_insert = SortInsert,
		.sort_choose = SortChoose,
		.sort_quickly = SortQuickly,
		.rand_arr = RandArr
	};
	int len;
	int choose;
	printf("请输入要生成的数组元素个数：\n");

	scanf("%d",&len);
	SORTARR.arr = SORTARR.rand_arr(len);
	printf("生成的数组为：\n");
	SORTARR.print_arr(SORTARR.arr,len);

	printf("（1）冒泡排序\t（2）插入排序\t（3）选择排序\t（4）快速排序\n");
	printf("请输入你要选择的排序方式序号，回车结束：\n");
	scanf("%d",&choose);

	switch(choose)
	{
	case 1:SORTARR.sort_bubble(SORTARR.arr,len);
		break;
	case 2:SORTARR.sort_insert(SORTARR.arr,len);
		break;
	case 3:SORTARR.sort_choose(SORTARR.arr,len);
		break;
	case 4:SORTARR.sort_quickly(SORTARR.arr,0,len);
		break;
	default:printf("其他排序方式正在研制中,请稍候...");
		break;
	}

	printf("排序后的数组为：\n");
	SORTARR.print_arr(SORTARR.arr,len);
	
	return 0;
}


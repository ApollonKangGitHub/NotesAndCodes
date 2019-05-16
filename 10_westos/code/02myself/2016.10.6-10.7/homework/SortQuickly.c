# include<stdio.h>

void QuicklySort(int *a,int low, int high);//�ݹ�������
int FindFlag(int *a,int low,int high);//flagǰ����flag��flag�󶼲���flagС���ҵ�flagλ��
void Print(int *a,int len);//�������

int main(void)
{
	int a[20]={12,19,-3,-8,4,2,5,1,9,7,-5,13,-2,8,22,-24,3,6,7,39};
	printf("����֮ǰ:\n");
	Print(a,20);
	QuicklySort(a,0,20);
	printf("����֮��\n");
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
	if(low < high)//�ⲿѭ����ֹ����
	{
		flag = FindFlag(a,low,high);
		QuicklySort(a,low,flag-1);//flag���ݹ�
		QuicklySort(a,flag+1,high);//flag�Ҳ�ݹ�
	}
}

int FindFlag(int *a,int low,int high)
{
	int key = a[low];
	while(low < high)//�ڲ�ѭ����ֹ����
	{
		while(low < high && (a[high] >= key))//�ô�low<high�����٣���Ϊÿ��һ��ѭ��high����ı�
			high--;
		a[low] = a[high];

		while(low < high && (a[low] <= key))//�ô�low<high�����٣���Ϊÿ��һ��ѭ��low����ı�
			low++;
		a[high] = a[low];
	}//After,high == low
	a[low] = key;	//a[high] = key;
	return low;		//return high;
}
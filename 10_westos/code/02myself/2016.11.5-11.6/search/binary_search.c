# include<stdio.h>

int binary_search(int *a,int key,int LEN)
{
	int low = 0,high = LEN;
	while(low<high)
	{
		if(key == a[(high+low)/2])
			break;
		else if(key > a[(high+low)/2])
			low = (high+low)/2 + 1;
		else
			high = (low+high)/2 - 1;
	}
	if(low<high)
		return (low+high)/2;
	else
		return -1;
}
int main(void)
{
	int key;
	int arr[15] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
	printf("请输入您要查询的数字：\n");
	scanf("%d",&key);
	int pos = binary_search(arr,key,15);
	if(pos == -1)
		printf("没找到！\n");
	else
		printf("该元素位置为:%d\n",pos+1);
	return 0;
}

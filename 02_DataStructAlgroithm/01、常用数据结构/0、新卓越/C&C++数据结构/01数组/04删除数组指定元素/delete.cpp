# include <stdio.h>
int delete_key(int * a,int n,int key);
int main (void)
{
	int data[15] = {12,23,45,4,56,4,67,4,12,29,4,4,7,6,4};
	int i;
	int key;
	printf("请输入你要删除的元素：\n");
	scanf("%d",&key);
	int n = delete_key(data,15,key);
	for(i=0; i<n; i++)
		printf("%4d",data[i]);
	putchar('\n');
	return 0;
}

int delete_key(int * a, int n, int key)
{
	int i=0;
	int j;

	while(i<n)
	{
		if(a[i] == key)
		{
			for(j=i; j<n; j++)
				a[j] = a[j+1];
				n--;
		}
		else
			i++;
	}
	return n;
}


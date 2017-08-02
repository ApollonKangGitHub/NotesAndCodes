# include<stdio.h>

void print(int *,int);
void sort_shell(int *,int);
int main (void)
{
	int a[10] = {1,-1,3,-6,5,7,2,9,12,4};

	print(a,10);
	sort_shell(a,10);
	print(a,10);
	return 0;
}

void sort_shell(int * a,int len)
{
	int i,j,n,tmp;
	n = len/2;
	while(n>0){
		//i从n开始,i每次加1(重点)
		for(i=n;i<len;i++){
			tmp = a[i];//每次进入第一个for循环，i前面的已经有序
			for(j=i-n; j>-1 && a[j]>tmp; j-=n)
				a[j+n] = a[j];
			a[j+n] = tmp;//第二个for循环结束处即为a[i]（tmp）插入处
		}
		n--;
	}
}

void print(int * a,int len)
{
	int i;
	for(i = 0;i<len;i++)
		printf("%d\t",a[i]);
	printf("\n");
}

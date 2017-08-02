/*
	2016年5月28日23:03:21
*/
# include <stdio.h>

int MergeProgram (int * a,int * b,int len_a,int len_b);

int main(void)
{
	int point;
	int data1[23] = {5,12,46,47,58,64,72,87,101,115,330};
	int data2[12] = {13,14,46,59,64,101,104,115,136,158,200,210}; 

	point = MergeProgram (data1,data2,11,12);//由于剔除了重复项，合并后的数组首元素下表为返回值k

	printf("不剔除重复项合并后data1[]为：\n");
	for(int i = 0; i<point; i++)
		printf("%-5d",data1[i]);
	putchar('\n');

	return 0;
}

int MergeProgram (int * a,int * b,int len_a,int len_b)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int point = len_a;

	/*
	while()循环最开始i<len_a-1,但是由于之后加了一个point“标兵”使a[]的长度发生变化，而没有改变判断条件致使99、101、158三个数据丢失
	while循环只负责比较a[]和b[]，当a[]与b[]只剩一个时就不需要再比较直接退出进行下一步for循环
	*/
	while(i < point && j < len_b)
	{
		if(a[i] < b[j])
			a[k] = a[i];
		else
		{
			for(int m = point; m >= i; m--)
				a[m] = a[m-1];
			a[k] = b[j];
			point ++;
			j ++;
		}

		i ++;
		k ++;
	}

	for(j,k; j<len_b ; j++,k++)
	{
		a[k] = b[j];
		point ++;
	}
	//最开始写了一个如果退出while时，b[]排完而a[]没有排完的类似于上面的for循环，最后发现没有必要，就删了。
	return point;
}

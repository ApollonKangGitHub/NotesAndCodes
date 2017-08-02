/*
	2016年5月28日23:06:34
*/

# include <stdio.h>

int MergeProgram (int * a,int * b,int len_a,int len_b);
void print(int * data,int low,int len);

int main(void)
{
	int point;
	int data1[23] = {5,12,46,47,58,64,72,87,101,115,330};
	int data2[12] = {13,14,46,59,64,101,104,115,136,158,200,210}; 
	
	printf("合并前data1[]和data2[]分别为：\n");
	print(data1,0,11);
	print(data2,0,12);

	point = MergeProgram (data1,data2,11,12);//由于剔除了重复项，合并后的数组首元素下表为返回值k

	printf("合并并剔除重复项后data1[]为：\n");
	print(data1,0,point);
	return 0;
}

int MergeProgram (int * a,int * b,int len_a,int len_b)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int point = len_a;
	/*while()循环最开始i<len_a-1,但是由于之后加了一个point“标兵”使a[]的长度发生变化，而没有改变判断条件致使99、101、158三个数据丢失*/
	while(i < point && j < len_b)
	{

		if(a[i] < b[j])
			a[k] = a[i];
		else if(a[i] > b[j])
		{
			for(int m = point; m >= i; m--)
				a[m] = a[m-1];
			a[k] = b[j];
			point ++;
			j ++;
		}
		else
		{
			a[k] = a[i];
			j++;
		}

		i ++;
		k ++;
	}

	for(j,k; j<len_b ; j++,k++)
	{
		a[k] = b[j];
		point ++;
	}
	return point;
}

void print(int * data,int low,int len)
{
	for(int i = low; i<len; i++)
		printf("%-5d",data[i]);
	putchar('\n');
}
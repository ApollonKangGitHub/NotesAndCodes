/*
	2016年6月5日10:09:14
*/
# include <stdio.h>
# define N 8
# define M 10

void MergeProgram(int *,int *,int *);//合并函数

int main (void)
{
	int data1[N] = {8,16,24,32,36,39,41,220};
	int data2[M] = {2,8,17,25,46,49,55,79,101,112};
	int data[M+N];
	MergeProgram(data1,data2,data);//可以不传递M和N，预定义所有函数都能使用

	for(int k=0;k<M+N;k++)
	printf("%-4d",data[k]);
	return 0;
}
/*
void MergeProgram(int *a,int *b,int *data)
{
	int i, j, k;
	for(i=0,j=0,k=0; i<N && j<M; k++)
	{
		if(a[i] > b[j])
		{
			data[k] = b[j];
			j++;
		}
		else
		{
			data[k] = a[i];
			i++;
		}
	}
/*
	int * s;
	int len, t;

    if(i<N)
	{
		s = a;
		t = i;
		len = N;
	}
    else 
	{
		s = b;
		t = j;
		len = M;
	}
	
	for(t;t<len;t++,k++)
		data[k] = a[t];	

*/
/*
	int * s = a;
	int len = N;
	if(j < M)
	{
		s = b;
		i = j;
		len = M;
	}
	for(i;i<len;i++,k++)
		data[k] = a[t];		  
*/
	for(i,k; i<N; k++,i++)
		data[k] = a[i];
	for(j,k; j<M; k++,j++)
		data[k] = b[j];//两个for循环只会执行一个
}

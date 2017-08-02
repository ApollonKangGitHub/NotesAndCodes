/*
	2016��6��5��11:13:54
*/
# include <stdio.h>
# define N 8
# define M 10

void MergeProgram(int *,int *,int *);//�ϲ�����

int main (void)
{
	int data1[N] = {8,16,24,32,36,39,41,220};
	int data2[M] = {2,8,17,25,46,49,55,79,101,112};
	int data[M+N];
	MergeProgram(data1,data2,data);//���Բ�����M��N��Ԥ�������к�������ʹ��

	for(int k=0;k<M+N;k++)
	printf("%-4d",data[k]);
	return 0;
}

void MergeProgram(int *a,int *b,int *data)
{
	int i=0, j=0, k=0;
	while(i<N || j<M)
	{
		if(j>=M || i<N && a[i]<b[j])//&&������ȼ�����||������i<N && a[i]<b[j]���ü�����
			data[k++] = a[i++];
		else
			data[k++] = b[j++];
	}
}

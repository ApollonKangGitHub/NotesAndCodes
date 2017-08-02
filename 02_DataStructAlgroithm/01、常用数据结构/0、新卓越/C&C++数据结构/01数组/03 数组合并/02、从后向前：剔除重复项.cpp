/*
	2016��5��27��13:27:34
*/
# include <stdio.h>

int MergeProgram (int * a,int * b,int len_a,int len_b);
void print(int * data,int low,int len);

int main (void)
{
	int k;
	int data1[23] = {5,12,32,46,58,64,72,87,99,101,246};
	int data2[12] = {13,14,46,58,69,101,104,115,136,158,200,290};

	k = MergeProgram (data1,data2,11,12);//�����޳����ظ���ϲ����������Ԫ���±�Ϊ����ֵk

	printf("�ϲ����޳��ظ����data1[]Ϊ��\n");
	print(data1,k+1,23);

	return 0;
}
int MergeProgram (int * a,int * b,int len_a,int len_b)
{
	int i = len_a - 1;
	int j = len_b - 1;
	int k = len_a + len_b - 1;
	
	while(i > -1 && j > -1)
	{
		if(a[i] > b[j]){
			a[k] = a[i];
			i--;
		}
		else if(a[i] < b[j]){
			a[k] = b[j];
			j--;
		}
		else{
			a[k] = a[i];
			i--;
			j--;
		}//������޳��ظ��ֻҪȥ�����һ��else����
		k--;
	}
	
	for(i,k; i>-1 && k>-1; i--,k--)		a[k] = a[i];
	for(j,k; j>-1 && k>-1; j--,k--)		a[k] = b[j];

	return k;
}

void print(int * data,int low,int len)
{
	for(int i = low; i<len; i++)
		printf("%-5d",data[i]);
	putchar('\n');
}
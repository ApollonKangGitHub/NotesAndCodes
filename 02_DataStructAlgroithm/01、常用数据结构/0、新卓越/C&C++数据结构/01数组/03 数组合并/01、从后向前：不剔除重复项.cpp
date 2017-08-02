/*
	2016Äê5ÔÂ27ÈÕ01:03:15
*/
# include <stdio.h>

void MergeProgram (int * a,int * b,int len_a,int len_b);

int main (void)
{
	int data1[23] = {5,12,32,46,58,64,72,87,99,101,112};
	int data2[12] = {13,14,46,58,69,101,104,115,136,158,200,210};

	MergeProgram (data1,data2,11,12);

	for(int i = 0; i<23; i++)
		printf("%-5d",data1[i]);
	printf("\n");
	return 0;
}
void MergeProgram (int * a,int * b,int len_a,int len_b)
{
	int i = len_a - 1;
	int j = len_b - 1;
	int k = 22;
	
	while(i > -1 && j > -1)
	{
		if(a[i] > b[j])
		{
			a[k] = a[i];
			i--;
		}
		else
		{
			a[k] = b[j];
			j--;
		}
		k--;
	}
	
	for(k,i; k>-1,i>-1; k--,i--)
		a[k] = a[i];
	for(k,j; k>-1,j>-1; k--,j--)
		a[k] = b[j];
	
}

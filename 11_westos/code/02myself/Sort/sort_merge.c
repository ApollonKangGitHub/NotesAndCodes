# include<stdio.h>

# define SIZE 20

void print(int *,int);
void merge(int *,int);
void sort_merge(int *, int, int *, int);

void print(int * a,int len)
{
	int i;
	for(i=0;i<len;i++)
		printf("%-5d",a[i]);
	printf("\n");
}

void merge(int *a,int len)
{
	if(len>1){
		int left_size = len/2;
		int right_size = len - left_size;
		int * left = a;
		int * right = a + left_size;
		merge(left,left_size);
		merge(right,right_size);
		sort_merge(left,left_size,right,right_size);
	}

}

void sort_merge(int * left, int left_size, int * right, int right_size)
{
	int i = 0, j = 0, k = 0;
	int tmp[SIZE] = {0};

	while(i<left_size || j<right_size)
		tmp[k++] = (j >= right_size || i<left_size && left[i] < right[j]) ? left[i++] : right[j++];

	  for(i = 0; i<k; i++)
		left[i] = tmp[i];
}
int main(void)
{
	int a[20] = {23,-2,3,8,1,-4,7,12,0,4,1,-2,7,23,32,34,12,9,-5,0};
	print(a,20);
	merge(a,20);
	print(a,20);
	return 0;
}


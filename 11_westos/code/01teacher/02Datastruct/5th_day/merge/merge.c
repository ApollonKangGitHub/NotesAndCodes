#include <stdio.h>

#define		SIZE	10

int merge(int *a, int n)
{
	if(n > 1){
		int list1_size = n/2;
		int list2_size = n - list1_size;
		int *list1 = a;
		int * list2 = a + list1_size;
		merge(list1, list1_size);
		merge(list2, list2_size);
		merge_sort(list1, list1_size, list2, list2_size);	
	}
		 
}
int merge_sort(int* list1, int list1_size, int* list2, int list2_size)
{
	int i = 0, j = 0, k = 0;
	int tmp[SIZE] = {0};

	while(i < list1_size && j < list2_size){
		if(list1[i] < list2[j])
			tmp[k++] = list1[i++];
		else 
			tmp[k++] = list2[j++];
	}
	while(i < list1_size)
		tmp[k++] = list1[i++];
	while(j < list2_size)
		tmp[k++] = list2[j++];

	for(i=0; i<k; i++)
		list1[i] = tmp[i];
}
int main()
{
	int a[8] = {10, 4, 6, 3, 8, 2, 5, 7};
	merge(a, 8);	
	
	int i = 0;
	for(i=0; i<8; i++)
		printf("%d\t", a[i]);
	printf("\n");

	return 0;
}









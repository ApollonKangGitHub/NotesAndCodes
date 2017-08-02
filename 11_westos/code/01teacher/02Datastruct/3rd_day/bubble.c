#include <stdio.h>

void bubble(int *a, int number);

int main(int a, char *b[])
{
	int arr[8] = {5, 4, 7, 3, 1, 9, 6, 2};
	
	bubble(arr, 8);
	
	int i = 0;
	for(i=0; i<8; i++)
		printf("%d\n", *(arr+i));
	
	return 0;
}

void bubble(int *a, int number)
{
	int i = 0;
	int j = 0;
	int tmp = 0;
	for(i=0; i<number; i++)
		for(j=0; j<number-1-i; j++)
			if(a[j] > a[j+1]){
				tmp = a[j];
				a[j] = a[j+1];
				a[j+1] = tmp;
			}
}










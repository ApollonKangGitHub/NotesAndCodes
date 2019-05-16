#include <stdio.h>

void choose(int *a, int number);

int main(int a, char *b[])
{
	int arr[8] = {15, 4, 17, 31, 11, 9, 6, 2};
	
	choose(arr, 8);
	
	int i = 0;
	while(i<8)
		printf("%d\n", arr[i++]);

	return 0;
}

void choose(int *a, int number)
{
	int i = 0;
	int j = 0;
	
	int max = 0;
	int tmp = 0;

	for(i=0; i<number; i++){
		max = 0;
		for(j=0; j<number-i; j++){
			if(a[max] < a[j])
				max = j;
		}
		tmp = a[max];
		a[max] = a[number-i-1];
		a[number-i-1] = tmp;
	}
}














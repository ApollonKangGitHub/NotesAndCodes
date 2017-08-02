#include <stdio.h>

void quick(int *s, int low, int high)
{
	if(high <= low)
		return;
	
	int i = low, j = high;
	int pivot = s[low];
	
	while(i < j) {
		while(i<j && s[j]>=pivot)
			j--;
		if(i<j){
			s[i] = s[j];
			i++;
		}	
		while(i<j && s[i]<=pivot)
			i++;
		if(i<j){
			s[j] = s[i];
			j--;
		}
	}
	
	s[i] = pivot;
	quick(s, low, i-1);
	quick(s, i+1, high);
}

int main(int argc, char *argv[])
{
	int s[8] = {33, 4, 1, 8, 50, 12, 9, 6};
	quick(s,0, 7);
	
	int i = 0;
	
	while(i < 8)
		printf("%d\t", s[i++]);
	printf("\n");
}












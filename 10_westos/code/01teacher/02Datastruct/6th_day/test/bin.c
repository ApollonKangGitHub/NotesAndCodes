#include <stdio.h>
#include <stdlib.h>

int bin(int *a, int low, int high, int key)
{
	int tmp = (low + high)/2;
	if(low > high)
		return -1;
	else if(key == a[tmp])
		return tmp;
	else if(key > a[tmp])
		return bin(a, tmp+1, high, key);
	else
		return bin(a, low, tmp-1, key);
	
}

int main()
{
	int a[11] = {3, 7, 9, 10, 22, 34, 40, 43, 49, 50, 77};
	
	int ret = bin(a, 0, 10, 50);
	if(ret < 0){
		printf("not found. \n");
		exit(1);
	}
	printf("ret: %d\n", ret);

	return 0;
}






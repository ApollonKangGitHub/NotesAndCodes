#include <stdio.h>

int main()
{
//	int a[5];
//	a[5] = {1, 2};   /error
//	a[5] = 10;  error

	int a[5] = {11, 21, 31, 41, 51};
//	int a[] = {1, 2};
//  数组名代表数组的首地址    
	
	int* pa = a;
	int i = 0;
	for(i=0; i<5; i++)
		printf("%d\n",*(pa+i));
		printf("a[%d]: %d\n", i, a[i]);
		printf("a[%d]: %d\n", i, *(a+i);
	


#if 0	
	int n = 5;
	int a[n];	//malloc(sizeof(int));
	int i = 0;

	for(i=0; i<5; i++)
		a[i] = 10 + i;
	for(i=0; i<5; i++)
		printf("a[%d]: %d\n", i, a[i]);
#endif
	return 0;
}






#include <stdio.h>
#include <string.h>

int main()
{
	//int a[5] = {10, 12, 35, 47, 58};
	int a[6] = {10, 12, 35, 47, 58};
	//int d = 20;	

	int i = 4;
	for(i=4; i>=0; i--)
		a[i+1] = a[i];

	for(i=0; i<6; i++)	
		printf("%d\t", a[i]);
	printf("\n");

#if 0
	printf("int: %d\n", sizeof(int));
	printf("a: %d\n", sizeof(a));
	int a[5];
	memset(a, 0, sizeof(a));
	int i = 0;

	for(i=0; i<5; i++)	
		printf("%d\t", a[i]);
	printf("\n");
#endif
	return 0;
}

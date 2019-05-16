#include <stdio.h>

int test(int (*pa)[4])
{

}
int main()
{
	int a[2][3] = { 11, 12, 13,
		       14, 15, 16,
		     };
	test(a);
//	int (*pa)[3] = NULL;
//	pa = a;
	int **pa = a;	//error
//	int (*pa)[3] = a;

	printf("1: %d\n", **pa);	
	printf("2: %d\n", *(*pa + 1));	
	printf("14: %d\n", **(pa + 1));	
	printf("15: %d\n", *(*(pa + 1) + 1));	
	


	return 0;
}











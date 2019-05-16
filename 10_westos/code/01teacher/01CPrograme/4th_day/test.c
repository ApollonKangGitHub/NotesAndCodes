#include <stdio.h>

void test(int (*pa)[3], int (*pb)[2])
{
	int i = 0, j = 0;
	for(i=0; i<2; i++){
		for(j=0; j<3; j++)
			*(*(pb + j)+i) = *(*(pa + i)+j);
	}
}
int main()
{
	int a[2][3] = { 11, 12, 13,
		       14, 15, 16,};
	int b[3][2] = {0};
	
	int a = 10;	
	test(a, b);

	int i = 0, j = 0;
	
	a = 100;
	for(i=0; i<3; i++){
		for(j=0; j<2; j++)
			printf("%d\t", b[i][j]);
		printf("\n");
	}
	
	return 0;
}











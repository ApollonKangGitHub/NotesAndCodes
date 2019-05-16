#include "test.h"


int main()
{
	int a[2][3] = { 11, 12, 13,
		       14, 15, 16,};
	int b[3][2] = {0};
	
	test(a, b);

	int i = 0, j = 0;

	for(i=0; i<3; i++){
		for(j=0; j<2; j++)
			printf("%d\t", b[i][j]);
		printf("\n");
	}
	
	ab();	
	dd();
	return 0;
}




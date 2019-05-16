#include <stdio.h>

int main()
{
	int a[2][3] = { 11, 12, 13,
		       14, 15, 16,};

	int (*pa)[3] = a;
	
	int i = 0, j = 0;
	for(i=0; i<2; i++){
		for(j=0; j<3; j++)
			printf("%d\t", *(*(pa+i)+j));
		printf("\n");
	}

	return 0;
}











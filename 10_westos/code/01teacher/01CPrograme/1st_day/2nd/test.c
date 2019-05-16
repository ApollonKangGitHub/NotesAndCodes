#include <stdio.h>

#define	M	6

int main()
{
	int a[M] = {11, 22, 33, 44, 55, 66};

	int i = 0, j = M-1, tmp;
	int *pa = a;

	while(i <= j){
		tmp = *(pa + i);
		*(pa + i) = *(pa + j);
		*(pa + j) = tmp;
		i++;
		j--;
	}

#if 1
	for(i=0; i<M; i++)
		printf("%d\n", *(pa+i));
#endif
	

	return 0;
}






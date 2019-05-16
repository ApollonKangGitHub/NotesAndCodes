#include "common.h"
void grape(int (*p)[4],int n)
{	
	int i,j;
	for(i=0;i<n;i++)
		for(j=0;j<3;j++)
			*(*(p+i)+3)+=*(*(p+i)+j);	
}

#include "test.h"




void test(int (*pa)[3], int (*pb)[2])
{
	int i = 0, j = 0;
	for(i=0; i<2; i++){
		for(j=0; j<3; j++)
			*(*(pb + j)+i) = *(*(pa + i)+j);
	}
}











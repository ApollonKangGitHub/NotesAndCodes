#include "test.h"

int sort(char** pps, int len)
{
	int i = 0, j = 0;
	char* tmp = NULL;
	for(i=0; i<len; i++){
		for(j=0; j<len-1-i; j++){
			if( (strcmp(*(pps+j), *(pps+j+1))) > 0){
				tmp = *(pps + j);
				*(pps + j) = *(pps + j +1);
				*(pps + j + 1) = tmp;
			}
		}
	}
}








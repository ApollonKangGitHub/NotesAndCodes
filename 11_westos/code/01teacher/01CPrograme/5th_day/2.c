#include <stdio.h>

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
int main()
{
	char* ps[4] = {"hello", "aorld", "shannxi", "xian"};

	sort(ps, 4);
	int i = 0;
	for(i=0; i<4; i++)
		printf("%s\n", *(ps + i));

	return 0;
}





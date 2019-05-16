#include <stdio.h>


int main()
{
	char* ps[4] = {"hello", "world", "shannxi", "xian"};
	char** pps = ps;

	printf(" %s \n", *pps);
	printf(" %c \n", **pps);

	printf(" %s \n", *(pps+1));

//	printf("ps[0]: %s\n", ps[0]);	

	return 0;
}





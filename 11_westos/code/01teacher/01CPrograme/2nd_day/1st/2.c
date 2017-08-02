#include <stdio.h>
#include <string.h>

int main()
{
//	printf("%d         %c   %s    %f        %p   %x      %o       %u   %zu ");
//	    signed int    char  char*  float   addr  16进制  8进制    unsigned int 
//						     addr

	printf("input int number : \n");
	int n;
	scanf("%d", &n);
	int a[n];
	
	int i = 0;
	for(i=0; i<n; i++)
		a[i] = i + 11;

	for(i=0; i<n; i++)
		printf("%d\t", a[i]);
	printf("\n");

	return 0;
}

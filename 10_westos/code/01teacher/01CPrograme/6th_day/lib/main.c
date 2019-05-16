#include <stdio.h>

char* mystrcpy(char*, char*);

int main()
{
	char dest[20] = {0};
	char *src = "hello test";

	char* pd = mystrcpy(dest, src);		
	printf("pd: %s\n", pd);

	return 0;
}






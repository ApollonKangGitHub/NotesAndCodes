#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <math.h>

#define	 S	12

char* mystrcpy(char* dest, char* src)
{
	char* tmp = dest;
	while(*src != '\0'){
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return tmp;	
}
char* test()
{
	char *src = "hello world";
//	char dest[12] = {0};

	char* dest = malloc(sizeof(char)*S);

	char* tmp = mystrcpy(dest, src);
	return tmp;
}
int main()
{
	char* tmp = test();
	printf("tmp: %s\n", tmp);
	
	free(tmp);
	return 0;
}





#include <stdio.h>
#include <string.h>

#if 0
void  mystrlen(char* pc , size_t* mylen)
{
	while(*pc != '\0'){
		(*mylen)++;
		pc++;	
	}
}
#endif

size_t mystrlen(char* pc )
{
	int count = 0;
	while(*pc != '\0'){
		count++;
		pc++;	
	}
	return count;
}
int main()
{
	size_t len = 0;
	char ch[12] = "hello world";	
	len = strlen(ch);
	
	printf("len: %u\n", len);

	return 0;	
}









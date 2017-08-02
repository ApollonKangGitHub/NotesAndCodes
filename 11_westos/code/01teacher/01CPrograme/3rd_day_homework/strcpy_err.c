#include <stdio.h>

//BSS 


char* mystrcpy(char* dest, char* src)
{
//	static int c = 200;
// 局部变量
	char* tmp = dest;
	while(*src != '\0'){
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
//	return tmp;	
}
char* test()
{
	char *src = "hello world";
	char dest[12] = {0};
	char* tmp = mystrcpy(dest, src);
	return tmp;
}
int main()
{
//	memset(dest, 0, sizeof(dest));
//	mystrcpy(dest, src);

	char* tmp = test();
	printf("tmp: %s", tmp);

	return 0;
}

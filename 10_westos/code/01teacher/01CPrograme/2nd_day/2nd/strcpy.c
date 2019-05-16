#include <stdio.h>

strncpy();
strcmp();
strstr();
atoi();
itoa();

int main()
{
	char* src = "hello world";
	char ch[12];
	
	int i = 0;	
/*
	while(*src != '\0'){
		ch[i] = *src;
		i++;
		src++;
	}
	ch[i] = '\0';
*/
	do {
		ch[i] = *src;
		i++;
		src++;
	}while(*src != '\0');

	printf("ch: %s\n", ch);	

	return 0;
}






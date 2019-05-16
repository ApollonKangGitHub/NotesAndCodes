#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
//	char ch = getchar();
//	printf("ch: %c\n", ch);

	FILE* fp = fopen("a.txt", "r");
	char c = fgetc(fp);
	fgetc(stdin);
	while(c != EOF)
	printf("c: %c\n", c);


	return 0;
}






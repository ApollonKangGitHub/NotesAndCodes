

























#include<stdio.h>
#include<stdlib.h>

int main (void)
{
	FILE * fp = fopen("test.txt","r");
	int ret = 0;

	while( (ret = getc(fp)) != EOF)
		putc(ret,stdout);

	fclose(fp);
	return 0;
}

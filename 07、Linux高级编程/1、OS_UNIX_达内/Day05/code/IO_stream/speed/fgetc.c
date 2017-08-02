

























#include<stdio.h>
#include<stdlib.h>

int main (void)
{
	FILE * fp = fopen("test.txt","r");
	int ret = 0;

	while( (ret = fgetc(fp)) != EOF)
		fputc(ret,stdout);

	fclose(fp);
	return 0;
}

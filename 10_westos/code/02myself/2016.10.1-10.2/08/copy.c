# include<stdio.h>
# include<stdlib.h>
# include<string.h>

int main(void)
{
	FILE * fp = fopen("a.txt","r");
	if(!fp)
	{
		perror("fopen err\n");
		exit(EXIT_FAILURE);
	}
	FILE * fp1 = fopen("b.txt","w");
	if(!fp)
	{
		perror("fopen err\n");
		exit(EXIT_FAILURE);
	}
	char ch;
	while((ch=getc(fp)) != EOF)
		putc(ch,fp1);

	fclose(fp);
	fclose(fp1);
	return 0;
}

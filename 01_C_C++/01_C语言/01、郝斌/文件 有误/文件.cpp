# include <stdio.h>
# include <stdlib.h>
# include <conio.h>
int main (void)
{

	FILE * fp;
	char str1[150];

	printf("请输入：\n");
	scanf("%s",str1);

	fp = fopen("test.txt","wt+");

	if(fp == NULL)
	{
		printf("文件打开失败！\n");
		getch();
		exit(1);
	}

	gets(str1);
	fputs(str1,fp);

	fclose(fp);

	return 0;
}
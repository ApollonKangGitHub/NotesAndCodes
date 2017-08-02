/*
	2016年5月31日17:34:11
	此程序大数只能是非负数
*/
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# define M 2000

void Add(char * a, char * b);

int main (void)
{
	char a[M], b[M];

	gets(a);
	gets(b);
	
	Add(a,b);
	printf("\n");
	return 0;
}


void Add(char a[], char b[])
{
	int num1[M] = {0}, num2[M] = {0};
	int i, j;
	int len1 = strlen(a);//strlen()函数在string.h中测字符串长度，类似于sizeof().
	int len2 = strlen(b);
	int max = __max(len1,len2);
	
	for(i = len1-1, j = 0; i > -1; i--, j++)
		num1[j] = a[i] - '0';
	for(i = len2-1, j = 0; i > -1; i--, j++)
		num2[j] = b[i] - '0';
	
	for(i = 0; i < max; i++)
	{
		num1[i] += num2[i];
		if(num1[i] > 9)
		{
			num1[i] -= 10;
			num1[i+1] ++;
		}
	}

	if(num1[max] == 0)
		max = max - 1;
		/*此处max为有效位最高位，如果num1[max]!=0说明num1[max]不是初始值0，而是进位1。大数相加要么最高位无进位，要么进位是1，没有其它情况。*/
	for(i = max; i > -1; i--)
		printf("%d",num1[i]);
}
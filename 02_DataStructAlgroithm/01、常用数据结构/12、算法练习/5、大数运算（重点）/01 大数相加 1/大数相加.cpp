/*
	2016��5��31��17:34:11
	�˳������ֻ���ǷǸ���
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
	int len1 = strlen(a);//strlen()������string.h�в��ַ������ȣ�������sizeof().
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
		/*�˴�maxΪ��Чλ���λ�����num1[max]!=0˵��num1[max]���ǳ�ʼֵ0�����ǽ�λ1���������Ҫô���λ�޽�λ��Ҫô��λ��1��û�����������*/
	for(i = max; i > -1; i--)
		printf("%d",num1[i]);
}
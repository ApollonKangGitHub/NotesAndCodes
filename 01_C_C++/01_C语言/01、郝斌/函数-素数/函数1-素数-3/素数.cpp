#include <stdio.h>
#include <stdlib.h>

bool IsPrime(int m)
{
	int i;
	for(i=2;i<m;i++)
	{
		if(0 == m%i)
			break;
	}
	if (i == m)
		return true;
	else
		return false;

}

int main(void)
{
	int val;
	int i;
	char ch;

	do
	{
		system("cls");
		system("color 5A");

		loop:printf("请输入要判断的数字:\n");//带有loop的语句与普通语句基本无差异，如果goto loop执行则跳到loop：语句往后开始执行，如果goto loop不执行，则loop：标号可以忽视
		scanf("%d", &val);
		system("cls");

		if(val<2)
		{
			printf("输入错误！请重新输入（大于1的数字）！\n");
			goto loop;//loop为语句标号，不可以作为函数标号。即goto不可以跨函数使用。语句标号可以在规定内随意规定（但整数不可以作为语句标号）
			//goto语句在高级语言中基本已经取消，C语言中尽管保留但是尽量不要使用
		}

		else
		{
			printf("1-%d之间的所有素数为：\n",val);

			for(i=1; i<=val; ++i)
			{
				if( IsPrime(i) )
					printf("%d\t",i);
			}

			printf("\n");

			printf("是否要继续？继续按Y，不继续按N.\n");
		}
		scanf(" %c", &ch); //%c前面必须得加一个空格
	}while(ch=='y'||ch=='Y');

	return 0;
}

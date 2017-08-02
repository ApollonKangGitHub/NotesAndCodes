/*
	2016年1月27日21:54:06
	目的：char的定义与赋值，ASCⅡ符号的对应的整数

*/

# include<stdio.h>
int main(void)
{
	char ch;	
	ch = 'A';//A 65
	printf("%c,%d\n",ch,ch);
	ch = 'B';//B 66//ch重新赋值
	printf("%c,%d\n",ch,ch);
	//ch = "C";//出错，字符串不可以赋值给ch，因为ch是字符不是字符串

	return 0;
}
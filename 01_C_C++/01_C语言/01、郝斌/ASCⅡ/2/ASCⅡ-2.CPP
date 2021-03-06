/*
	2016年1月27日21:55:32
	目的：了解ASCⅡ的含义，测试ASCⅡ的字符与进制的转换
*/


# include<stdio.h>

int main(void)
{
	char ch = '0';
	printf("%c,%d,%o,%x\n",ch,ch,ch,ch);//符号‘0’，ASCⅡ值为48,48化为八进制为60,化为十六进制为30
	ch = '3';//重新赋值
	printf("%c,%d,%o,%x\n",ch,ch,ch,ch);//符号‘3’，ASCⅡ值为51,51化为八进制为63,化为十六进制为33
	ch = '=';
	printf("%c,%d,%o,%x\n",ch,ch,ch,ch);//符号‘=’，ASCⅡ值为61,61化为八进制为75,化为十六进制为3d

	return 0;
}

/*
在VC++6.0中输出结果为；
0,48,60,30
3,51,63,33
=,61,75,3d
*/

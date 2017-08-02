/*
	2016年1月27日21:52:24
	目的：测试控制符%d,%o,%x,%X，%#x,%#X的用法
*/

# include <stdio.h>
int main(void)
{
	int i = 29;
	printf("%d,%o,%x,%X，%#x,%#X\n",i,i,i,i,i,i);//%x输出小写，%X输出大写
	return 0;
}

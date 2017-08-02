/* upper.c */
#include <stdio.h>
int main(void)
{
	int ch;
	while((ch = getchar()) != EOF) {
		putchar(toupper(ch));//将小写字母转换成大写，按Ctrl+d退出
	}
	return 0;
}

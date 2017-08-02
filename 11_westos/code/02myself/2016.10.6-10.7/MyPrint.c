#include <stdio.h>
#include <stdarg.h>

int Print_int(int a)
{
	int c;
	int pos = 0;
	while(pos != 1)
	{
		pos = 1;
		c = a;
		while(c > 9)
		{
			c = c / 10;
			pos = pos * 10;
		}
		putchar(c+48);
		a = a % pos;
	}
}

int myprintf(char* str, ...)
{
	va_list tt;
	va_start(tt, str);
	
	while(*str != '\0'){
		
		if(*str != '%'){
			putchar(*str);
			str++;
			continue;
		}
		str++;
		switch(*str){
			case '%':
				putchar('%');
				str--;
				break;
			case 'd':
				Print_int(va_arg(tt, int));
				break;
			default:
				putchar('%');
				putchar(*str);
				break;
		}
		str++;
	}
	va_end(tt);
}

int main()
{
	int a = 83242;
	char c = 'x';	
	int b = 12342;
	myprintf("a:%d\nc:%d\n", a, b);

	return 0;
}


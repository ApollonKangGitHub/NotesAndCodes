#include <stdio.h>
#include <stdarg.h>

/*   /include/acpi/platform/acenv.h	
 *   typedef char*	va_list;
 *   va_list 
 *
 *   va_start(tt, str)	 以str为起点，并 获取str的首地址, 无返回值。
 *   va_arg(tt, type)	 返回当前type类型参数的值
 *   va_end(tt)		tt = NULL


 							int 
	#define  _AUPBND                (sizeof (acpi_native_int) - 1)
	#define  _ADNBND                (sizeof (acpi_native_int) - 1)

	Variable argument list macro definitions
#define _bnd(X, bnd)            (((sizeof (X)) + (bnd)) & (~(bnd)))

#define va_arg(ap, T)           (*(T *)(((ap) += (_bnd (T, _AUPBND))) - (_bnd (T,_ADNBND)))    )
#define va_end(ap)              (void) 0
#define va_start(ap, A)         (void) ((ap) = (((char *) &(A)) + (_bnd (A,_AUPBND))))
 

*/

int pri_char(char c)
{
	putchar(c);
}
int ten(int a)
{
	putchar(a + 48);
}
int myprintf(char* str, ...)
{
	va_list tt;
	va_start(tt, str);
	while(*str != '\0'){
		if(*str != '%'){
			putchar(*str);
//			continue;
		}
		
		switch(*str){
			case '%':
		//		putchar('%');
				break;
			case 'd':
				ten(va_arg(tt, int));				
				str++;				
				break;
			case 'c':
				pri_char((char)va_arg(tt, int));
				str++;
				break;
		}
		
	}
	va_end(tt);
}

int main()
{
//	int a = 8;
//	char c = 'x';	
//	int b = 1;

//	myprintf("a: %d c: %c\n", a, c);

	return 0;
}






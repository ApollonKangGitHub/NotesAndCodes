#include <stdio.h>
#include <stdarg.h>

void print_int(int num)
{
	if(num==0) 
		return;
	print_int(num/10);
	putchar(num%10+'0');
}
void print_oct(unsigned int num)
{
	if(num == 0)
		return;
  
	print_int(num/8);
	putchar(num%8+'0');
}
int myprintf(const char *str,...)
{
	int i;
	va_list tt;
	char    ch;

	va_start(tt,str);
	for(i=0;str[i];i++){
		if(str[i]!='%'){ //普通字符
			putchar(str[i]);
			continue;
	  	}
	 	 ch=str[++i];
	 	 switch(ch){
	 	 	case '%':
	 	       	putchar('%');
	 	       	break;
	 	   	case 'd':
	 	     		print_int(va_arg(tt,int));
	 	   		break;
	 	   	case 'o':
	 	     		print_oct(va_arg(tt,unsigned int));
	 	     		break;
		}	
	}
	va_end(tt);
}

int main(void)
{
	int a=10;

	printf("is test==> %%%%  %d a:%o\n",a,a);

	return 0;
}











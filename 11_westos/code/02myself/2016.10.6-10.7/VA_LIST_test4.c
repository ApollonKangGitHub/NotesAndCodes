#include<stdio.h>
#include<stdarg.h>
/*calculatesum ofa 0 terminated list */
void sum(char*msg, ...);
int main(int argc,char*argv[])
{
	sum("The total is %d,rigth?\n",1,2,3,4,5,0);
	return 0;
}
void sum(char*msg, ...)
{
	int total=0;
	int arg;
	va_list ap;
	va_start(ap,msg); /*ap指向第一个可变参数*/
	while ((arg=va_arg(ap,int))!=0)
	{
		total+= arg;
	}
	printf(msg, total);
	va_end(ap);
}
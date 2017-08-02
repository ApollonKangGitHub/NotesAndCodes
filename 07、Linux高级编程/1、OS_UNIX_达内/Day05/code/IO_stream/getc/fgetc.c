




































#include<stdio.h>
int main(void){
	int ret_putc = fputc('1',stdout);	
	printf("ret_putc:%d,%c\n",ret_putc,ret_putc);
		
	int ret_getc = fgetc(stdin);
	printf("ret_getc:%d,%c\n",ret_getc,ret_getc);

	return 0;
}

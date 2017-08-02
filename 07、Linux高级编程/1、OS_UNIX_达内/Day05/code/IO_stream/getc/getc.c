

























#include<stdio.h>
#include<stdlib.h>

int main(void){
	FILE * fp = fopen("a.txt","wr+");
	if(fp == NULL){
		printf("open a.txt error\n");
		exit(EXIT_FAILURE);
	}
	int ret_putc = putc('1',fp);	
	printf("ret_putc:%d,%c\n",ret_putc,ret_putc);
//	putc('2',fp);
	fclose(fp);
	fp = fopen("a.txt","r");
	getc(fp);
	int ret_getc = getc(fp);
	printf("ret_getc:%d,%c\n",ret_getc,ret_getc);

	fclose(fp);
	return 0;

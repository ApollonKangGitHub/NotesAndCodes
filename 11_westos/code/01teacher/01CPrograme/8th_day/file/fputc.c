#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
	FILE* fp1 = fopen(argv[1], "r");			
	if(NULL == fp1){
		perror("fopen err.");
		exit(EXIT_FAILURE);
	}
	FILE* fp2 = fopen(argv[2], "w");			
	if(NULL == fp2){
		perror("fopen err.");
		exit(EXIT_FAILURE);
	}
	char ch;

	while((ch = fgetc(fp1)) != EOF)	
		fputc(ch, fp2);
	
	fclose(fp1);
	fclose(fp2);
	
	return 0;
}






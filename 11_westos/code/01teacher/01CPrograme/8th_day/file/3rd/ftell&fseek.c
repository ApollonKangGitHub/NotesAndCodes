#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
	FILE* fp = fopen(argv[1], "r");			
	if(NULL == fp){
		perror("fopen err.");
		exit(EXIT_FAILURE);
	}
	fgetc(fp);
	fgetc(fp);
	fgetc(fp);
	long off = ftell(fp);	
	printf("off: %d\n", off);
	rewind(fp);
	off = ftell(fp);	
	printf("off: %d\n", off);

	fseek(fp, 10, SEEK_SET);   
	fseek(fp, -10, SEEK_CUR);	  
	fseek(fp, 10, SEEK_END);  


	fclose(fp);
	
	return 0;
}






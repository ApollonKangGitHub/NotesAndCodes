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
	FILE* fp2 = fopen("b.txt", "w");			
	if(NULL == fp2){
		perror("fopen err.");
		exit(EXIT_FAILURE);
	}

	char buf[100] = {0};
	while((fgets(buf, sizeof(buf), fp1)) != EOF)
		fputs(buf, fp2);
			
	fclose(fp1);
	fclose(fp2);
	
	return 0;
}






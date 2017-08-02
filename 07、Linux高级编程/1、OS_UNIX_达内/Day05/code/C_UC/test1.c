#include<stdio.h>
#include<stdlib.h>

#define MAX 1000000

int main (void)
{
	FILE * fp = fopen("test1.txt","w");
	if(fp == NULL){
		perror("fopen test1.txt");
		exit(EXIT_FAILURE);
	}

	int i;
	for(i = 0; i < MAX; i++){
		fwrite(&i, sizeof(int), 1, fp);
	}

	fclose(fp);
	return 0;
}

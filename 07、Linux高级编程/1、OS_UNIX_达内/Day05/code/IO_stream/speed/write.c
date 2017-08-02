

























#include<stdio.h>
#include<stdlib.h>

#define MAX 100000000
int main (void)
{
	FILE * fp = fopen("test.txt","w+");
	int ret = 0;
	int i = 1;
	char buf[] = "abcdefghijklmnopqrstuvwxyz";
	for(i; i< MAX; i++){
		fwrite(buf,1,sizeof(buf),fp);
	}

	fclose(fp);
	return 0;
}

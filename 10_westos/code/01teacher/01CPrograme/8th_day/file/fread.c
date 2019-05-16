#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	FILE* fp = fopen("a.txt", "r");
	if(NULL == fp){
		perror("fopen err\n");
		exit(EXIT_FAILURE);
	}

	char buf[20] = {0};

	int num = fread(buf, 1, sizeof(buf)-1, fp);
	if(num <= 0){
		perror("fread err.\n");
		exit(EXIT_FAILURE);
	}
	printf("num: %d\n", num);
	printf("buf: %s\n", buf);
	fclose(fp);

	return 0;
}






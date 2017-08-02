#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	FILE* fp = fopen("a.txt", "w");
	if(NULL == fp){
		perror("fopen err\n");
		return 1;
	}
	char buf[30] = "hello file";

	int num = fwrite(buf, 1, 20, fp);
	if(num <= 0){
		perror("fwrite err.\n");
		exit(EXIT_FAILURE);
	}
	printf("num: %d\n", num);
	fclose(fp);
	return 0;
}






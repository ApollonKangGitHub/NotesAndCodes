#include <stdio.h>
#include <string.h>

int main()
{
//	FILE_STDIN  FILE_STDOUT  FILE_STDERR	
//	stdin   stdout   stderr 
	
	FILE* fp = fopen("a.txt", "w");
	if(NULL == fp){
		//printf("fopen err\n");
		perror("fopen err\n");
		return 1;
	}
	char* buf = "hello file";
	int num = fwrite(buf, 1, strlen(buf), fp);
	if(num <= 0){
		perror("fwrite err.\n");
	//	exit(1);
		exit(EXIT_FAILURE);
	}

//	printf("eof: %d\n", EOF);

	fclose(fp);
	return 0;
}






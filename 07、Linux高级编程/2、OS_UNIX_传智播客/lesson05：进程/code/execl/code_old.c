#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main(void)
{
	printf("hello\n");

	int ret = execl("/home/krj/test/code_new",
	"./code_new","everyone","I","am","zhangfei",NULL);
	if(ret == -1){
		perror("execl");
		exit(EXIT_FAILURE);
	}
	printf("world\n");
	return 4;
}

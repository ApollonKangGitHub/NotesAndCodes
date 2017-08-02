# include<stdio.h>
# include<errno.h>
int main(void)
{
	FILE * fd = fopen("./aaaaaaaa.txt","r");
	if(fd == NULL)
		printf("open: %m\n");
//	printf("open: %s\n",strerror(errno));
	FILE * fd2 = fopen("./test.c","r");
	if(fd2 == NULL)
		perror("open");

	return 0;
}

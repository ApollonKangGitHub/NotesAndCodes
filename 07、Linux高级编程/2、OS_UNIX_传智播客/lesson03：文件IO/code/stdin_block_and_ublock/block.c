#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#define SIZE 1024

int main(void)
{
	char buf[SIZE] = {0};
	int ret = read(STDIN_FILENO, buf, sizeof(buf));
	write(STDOUT_FILENO, buf, ret);

	return 0;
}

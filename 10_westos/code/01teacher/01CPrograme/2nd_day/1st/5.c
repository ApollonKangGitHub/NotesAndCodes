#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
	char ch[6] = "hello";
	char* ps = "hello";

	char* ps = ch;
	*(ps + 3) = 'w';	

	printf("ps: %s\n", ps);
	char* ph = "hello";
	*(ph + 3) = 'w';

	printf("ph: %s\n", ph);
	
	int i = 0;
	for(i=0; i<6; i++)
		printf("%c\t", *(ps + i));
	printf("\n");

	return 0;
}

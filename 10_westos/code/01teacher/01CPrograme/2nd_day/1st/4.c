#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
	int a[5] = {1, 2, 3, 4, 5};
	
//	char ch[7] = {'h', 'e', 'l', '\0', 'l', 'o', '\0'};
//	char ch[5] = {'h', 'e', 'l', 'l', 'o'};
	char ch[6] = "hello";
	char* ps = "hello";
//		"hello";
	
	printf("ch : %s\n", ch);
	printf("ps : %s\n", ps);
//	NULL       -0.0001  < f < 0.0001
//		NULL     0     '\0'     
	int i = 0;
	for(i=0; i<5; i++)
		printf("%c\t", ch[i]);
	printf("\n");

	return 0;
}

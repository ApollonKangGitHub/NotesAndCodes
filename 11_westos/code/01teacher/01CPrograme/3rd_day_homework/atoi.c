#include <stdio.h>

int myatoi(char* p)
{
#if 1
	printf("myatoi \n");
	int sum = 0;
	int d = 0;
	int flag = 1;

	if(*p == '-'){
		flag = -1;
		p++;	
	}
	printf("while \n");
	while(*p != '\0' && *p != '.'){
		d = *p - 48;		
		sum = sum*10 + flag*d;
		p++;
	}	
	return sum;
#endif
}

int main()
{
	char* pi = "-123489.438";
	int data = 0;

	data = myatoi(pi);
	printf("data: %d\n", data);

	return 0;
}








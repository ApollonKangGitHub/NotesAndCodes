#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* myitoa(int data, char** ps)
{
	*ps = malloc(sizeof(char)*12);
	memset(*ps, 0, sizeof(char)*12);
	int i = 10;

	while(data){
		*(*ps+i) = data%10 + 48;
		data /= 10;
		i--;
	}
	i++;
	return (*ps+i);
}
int main()
{
	int data = 1234;
	char* pa = NULL;

	char* ps = myitoa(data, &pa);		
	printf("ps: %s\n", ps);

	free(pa);
	return 0;
}






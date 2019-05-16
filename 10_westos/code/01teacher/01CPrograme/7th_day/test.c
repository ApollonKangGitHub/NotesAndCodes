#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person {
	int age;
	char* name;
	int (*peat)(char*);
	int (*pstudy)(char*, char*);
};

int he(char* name)
{
	printf(" 我 都  吃 了 ！！\n");

	return 0;
} 
int abc(char* math, char* c)
{
	printf("都 不 会 ！！\n");

	return 0;
}
//---------------------------------------------------

struct person jim = {
	.peat = he,
	.pstudy = abc,	
};

//-------------------------    app --------------------
int main()
{
	jim.peat("mian");
	jim.pstudy("math", "C");

	return 0;
}













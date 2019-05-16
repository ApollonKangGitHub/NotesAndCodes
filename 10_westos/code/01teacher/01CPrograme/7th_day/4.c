#include <stdio.h>

#pragma pack(8)

struct person{
	int age;
	char* name;
	//double id;
	float f;
	short b;
	char e[9];
	char g;
	char h;
	char r;
};

int main()
{
	printf("size: %d\n", sizeof(struct person));

	return 0;
}







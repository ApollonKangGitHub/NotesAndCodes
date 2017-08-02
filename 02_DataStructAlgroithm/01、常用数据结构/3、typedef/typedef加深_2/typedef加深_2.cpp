# include <stdio.h>

typedef struct Student 
{
	int sid;
	char name[100];
	char sex;
}* PSTU, STU;//STU 代表了struct Student，PSTU代表了struct Student *

int main (void)
{
	STU st;
	PSTU ps = &st;
	ps->sid = 99;
	printf("%d\n",ps->sid);

	return 0;
}


# include <stdio.h>
# include <string.h>

struct Student
{
	int sid;
	char name[100];
	int age;
};
void input1(struct Student *pst);
void input2(struct Student *pst);
void output(struct Student *pst);
int main (void)
{
	
	struct Student st;

	input1(&st);
	output(&st);
	input2(&st);
	output(&st);

	return 0;
}

void input1(struct Student *pst)
{
	(*pst).sid = 99;
	strcpy((*pst).name,"lisi");
	(*pst).age = 19;
}

void input2(struct Student *pst)
{
	pst->sid = 102;
	strcpy(pst->name,"wangwu");
	pst->age = 21;
}

void output(struct Student *pst)
{
	printf("%d  %s  %d\n",pst->sid,pst->name,pst->age);
}

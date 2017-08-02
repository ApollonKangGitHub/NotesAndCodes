#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person{
	int age;
//	char name[20];
	char* name;
	long long id;
//	struct person* lily;
//	struct man jim;	
};

int test(struct person* lily)
{

}
int main()
{
#if 0
	int a;
	struct person jim;
//	printf("size: %d\n", sizeof(jim));	

	jim.age = 30;
	jim.id = 12345678;
//	jim.name[20] = "jim";		
//	strcpy(jim.name, "jim");	
	jim.name = "jim";	
	test(&jim);
	printf("age: %d\n", jim.age);
	printf("name: %s\n", jim.name);
#endif
//---------------------------------------------------	
	
	struct person*  p;
	p = malloc(sizeof(struct person));

	p->age = 20;
	
	printf("age: %d\n", p->age);

	free(p);
	p = NULL;

	return 0;
}







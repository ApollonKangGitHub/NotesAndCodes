#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person{
	int age;
	char* name;
	long long id;
};

int main()
{
	int a = 10, b = 20;

	struct person jim = {
		.age = 20,
		.name = "jim",
		.id = 123456,
	};

	printf("age: %d\n", jim.age);
	printf("name: %s\n", jim.name);


	return 0;
}







#include <stdio.h>

struct data{
	int age;
	int score;
	char* name;
};


int main()
{
	int a[3] = {1, 2, 3};
	struct data b[3];

	struct data a;
	struct data b;
	struct data c;

	b[0].age = 100;
	b[0].score = 200;
	b[1] = {};
	b[2] = {};
	
}

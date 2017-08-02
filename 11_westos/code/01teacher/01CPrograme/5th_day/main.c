#include "test.h"

int main()
{
	char* ps[4] = {"hello", "aorld", "shannxi", "xian"};

	sort(ps, 4);
	int i = 0;
	for(i=0; i<4; i++)
		printf("%s\n", *(ps + i));

	return 0;
}





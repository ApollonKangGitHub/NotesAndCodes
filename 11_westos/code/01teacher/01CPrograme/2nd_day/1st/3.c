#include <stdio.h>
#include <string.h>

//int main()
//int main(void)
int main(int argc, char* argv[])
//int main(int argc, char** argv)
{

	int d = atoi(argv[1]);
	printf("d: %d\n", d);

	printf("argc: %d\n", argc);
	printf("argv[0] %s\n", argv[0]);
	printf("argv[1] %d\n", atoi(argv[1]));
	printf("argv[2] %d\n", argv[2]);
	printf("argv[3] %d\n", argv[3]);
#if 0
	int a[n];
	int i = 0;
	for(i=0; i<n; i++)
		a[i] = i + 11;

	for(i=0; i<n; i++)
		printf("%d\t", a[i]);
	printf("\n");
#endif
	return 0;
}

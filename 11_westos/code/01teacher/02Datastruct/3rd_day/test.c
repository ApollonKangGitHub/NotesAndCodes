#include <stdio.h>
#include <time.h>

int main()
{
#if 0
	clock_t start = clock();	
	sleep(3);
	clock_t end = clock();	
	printf("timeuse: %d\n", end-start);
#endif

	float f = 4.40;
//	printf("%f %d\n", f, f);	

	printf("%d %f\n", f, f);	

	return 0;
}





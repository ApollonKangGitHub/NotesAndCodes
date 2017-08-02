#include <stdio.h>

int main()
{
	printf("line: %d\n", __LINE__);
	printf("file: %s\n", __FILE__);
	printf("date: %s\n", __DATE__);
	printf("time: %s\n", __TIME__);
	printf("function: %s\n", __FUNCTION__); 

	srand(time(NULL));
	int i = 0;
	for(i=0; i<10; i++) 
//		printf("%d  ",rand()%100);
//		printf("%d  ", rand()%44 + 16);
		printf("%d  ", rand()%11 + 20);
//			20 -- 30  
		//  [16 --- 59]     [16,   59 = (44 + 16 - 1)]
	printf("\n");

	return 0;
}






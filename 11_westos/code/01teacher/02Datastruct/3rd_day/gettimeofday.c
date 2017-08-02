#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
 
int main() 
{
	struct timeval start;
	struct timeval end;

	gettimeofday( &start, NULL );
	int i = 0;
	int a[5000];
	memset(a, 0, sizeof(a));
	while(i < 2000){	
		i++;
		a[i] = i + 10;
	}

	gettimeofday( &end, NULL );
	suseconds_t timeuse = ( end.tv_usec - start.tv_usec ) ;
	    printf("time: %u us\n", timeuse);
	    return 0;
}






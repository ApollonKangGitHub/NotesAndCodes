#include <stdio.h>

#define _32BIT	1

int main()
{

#if 1
//#ifdef  _32BIT	
	printf("x86_32 bits \n");		
#else 
	printf("x86_64 bits \n");		
#endif
	
	return 0;	
}









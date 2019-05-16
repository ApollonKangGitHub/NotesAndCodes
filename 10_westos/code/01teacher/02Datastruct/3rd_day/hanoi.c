#include <stdio.h>

int move(int n, char x, char y, char z)
{
	if(n == 1)
		printf("%c--->%c\n", x, z);
	else{
		move(n-1, x, z, y);
		printf("%c--->%c\t", x, z);
		move(n-1, y, x, z);
	}
}

int main()
{
	int n = 3;
	
	move(n, 'A', 'B', 'C');
	
}




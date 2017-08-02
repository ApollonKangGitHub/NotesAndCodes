# include <stdio.h>
# include <setjmp.h>
# include <stdlib.h>
static jmp_buf buf;
int main(void)
{
    volatile int b = 3;
    if (setjmp(buf) != 0)
    {
   		printf("%d\n", b);
    	exit(0);
    }
    b = 5;
    longjmp(buf, 1);
	return 0;
}


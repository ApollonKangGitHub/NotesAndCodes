# include <stdio.h>
# include <malloc.h>

int main (void)
{
	while (1)
	{
		int *p = (int *)malloc(1000);//括号中数字决定死机快慢，数字越大死机速度越快

		//free(p);//可将p所指向内存释放，以此达到消除该病毒的目的
	}
	return 0;
}
#include<stdio.h>
int main(void)
{
	void * ptr = NULL;
	ptr--;//按理来说不能运行，因为void* 类型的指针不知到减多少
	
//	void a;

	return 0;
}

#include <stdio.h>


int test(int a, char* ps)
{
	printf("a: %d\n", a);
	printf("ps: %s\n", ps);

	return 0;
}

int main()
{
	test(100, "hello test");	
//	函数指针： 指向函数的指针（保存函数的入口地址）
//	通过函数指针调用函数  
//	pt（100， "hello test"）

	int (*pt)(int, char*);
	pt = test;
	printf("pt: 0x%x\n", pt);
	pt(100, "hello test");

	return 0;
}












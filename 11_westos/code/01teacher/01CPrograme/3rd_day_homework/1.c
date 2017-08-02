#include <stdio.h>

void* test(void* x, void* y)
{
	int a = (*(int*)x);
	int b = (*(int*)y);
	
	a = a + b;
	return (void*)a;
}

int main()
{
//	void   只能修饰函数，不能修饰变量 
//	void * 函数、变量都可以被修饰 
	
	int a = 100;
	int b = 200;
	int pa = (int)test(&a, &b); 	
	printf(" value: 0x%x\n", pa);

	return 0;
} 

















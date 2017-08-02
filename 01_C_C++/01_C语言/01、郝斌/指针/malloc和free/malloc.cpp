/*
	2016年3月14日18:31:21
	malloc 是 memory(内存) allocate(分配)的缩写

*/
# include <stdio.h>
# include <malloc.h>  
# include <stdlib.h>
int main(void)
{
	system("color f0");

	int i = 5; //分配了4个字节 静态分配
	int * p = (int *)malloc(4); //分配了4个字节 动态分配
	printf("%d,%d\n\n\n",i,*p);//输出5，乱码（p指向有内存无内容）

	*p = 10; //*p 代表的就是一个int变量， 只不过*p这个整型变量的内存分配方式和11行的i变量的分配方式不同
	printf("%d,%d\n\n\n",i,*p);//输出5，10

	free(p); //freep(p)表示把p所指向的内存给释放掉 
	p = NULL;//为了防止p所指向内存释放后，系统随意给p一个地址时产生安全隐患。
	printf("%d,%d\n\n\n",i,*p);//输出5，乱码（p指向无内存，内存已释放）

	return 0;
}

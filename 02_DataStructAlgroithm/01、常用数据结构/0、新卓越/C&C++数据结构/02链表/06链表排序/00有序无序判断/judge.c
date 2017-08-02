/*
	2016年8月24日11:02:54修改
	最初用.cpp文件编译位出错，换成.c文件需要将原有的bool类型换成int。
	并且#define true与false才可以消除C与C++的差别带来的错误
*/
# include <stdio.h>
# include <stdlib.h>
# include "link.h"
# define false 0
# define true 1

int AscendingOrder_Link(PNODE pHead);//升序判断
int DescendingOrder_Link(PNODE pHead);//降序判断

int main (void)
{
	PNODE pHead;
	int a[10] = {18,18,20,21,28,31,31,39,44,44};
	pHead = BackwardCreate_Link(a,10);
	ForwardTraversal_Link(pHead);

	if(AscendingOrder_Link(pHead))
		printf("升序有序!\n");
	else
		printf("升序无序!\n");

	if(DescendingOrder_Link(pHead))
		printf("降序有序!\n");
	else
		printf("降序无序!\n");

	return 0;
}

int AscendingOrder_Link(PNODE pHead)
{
	PNODE p = pHead;
	for(p; p->pNext; p=p->pNext)
		if(p->data > p->pNext->data)
			return false;
	return true;
}


int DescendingOrder_Link(PNODE pHead)
{
	PNODE p = pHead;
		for(p; p->pNext; p=p->pNext)
			if(p->data < p->pNext->data)
				return false;
		return true;
}

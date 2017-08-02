/*
	2016年7月17日15:37:56	
*/
# include <stdio.h>
# include <stdlib.h>
# include "link.h"

void DeletepIn_link(PNODE p);
int main (void)
{
	int a[8] = {3,2,7,6,9,5,10,8};
	PNODE pHead;
	pHead = FowardCreate_Link(a,8);
	ForwardTraversal_Link(pHead);

	DeletepIn_link(pHead->pNext->pNext);//送往被调函数的并非头指针
	ForwardTraversal_Link(pHead);

	return 0;
}

/*
删除未知头指针，却知链表中间一个节点的地址（pIn指向该节点）。如何删除该节点？
*/
void DeletepIn_link(PNODE pIn)
{
	PNODE pDel = pIn->pNext;
	int temp = pIn->data;
	pIn->data = pDel->data;
	pDel->data = temp;
	pIn->pNext = pDel->pNext;
	free(pDel);

	printf("删除任意位置节点结果为:\n");
}
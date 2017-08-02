/*
	2016年7月24日12:13:11
	逆向建链合并
*/
# include <stdio.h>
# include <stdlib.h>
# include "link.h"

PNODE MergeOne_Link(PNODE pHeadA, PNODE pHeadB);
PNODE BackTravInverse_Link(PNODE pHead);

int main (void)
{
	PNODE pHead = NULL;
	PNODE pHeadA = NULL;
	PNODE pHeadB = NULL;

	int a[10] = {1,3,6,11,15,22,37,57,61,85};
	int b[10] = {2,4,6,11,15,32,37,44,68,85};

	printf("链表A:\n");
	pHeadA = FowardCreate_Link(a,10);
	ForwardTraversal_Link(pHeadA);
	printf("链表B:\n");
	pHeadB = FowardCreate_Link(b,1);
	ForwardTraversal_Link(pHeadB);
	printf("合并后:\n");
	pHead = MergeOne_Link(pHeadA,pHeadB);
	ForwardTraversal_Link(pHead);

	return 0;
}
/*逆向建链合并法*/
PNODE MergeOne_Link(PNODE pHeadA, PNODE pHeadB)//两个升序链表合并成一个升序链表
{
	PNODE pHead = NULL;
	PNODE p;

	for(; pHeadA || pHeadB; p->pNext = pHead,pHead = p)//能够进入循环pHeadA和pHeadB中至少有一个不为空
	{
		if(pHeadB==NULL || (pHeadA && (pHeadA->data <= pHeadB->data)))//而当pHeadB，pHeadA都不为空才能执行数据判断，否则其中一个没有数据域
		{
			p = pHeadA;
			pHeadA = pHeadA->pNext;
		}
		else
		{
			p = pHeadB;
			pHeadB = pHeadB->pNext;
		}
	}
	pHead = BackTravInverse_Link(pHead);//调用倒置函数以前，合并的链表为降序有序
	return pHead;
}
/*倒置函数*/
PNODE BackTravInverse_Link(PNODE pHead)
{
	PNODE q = pHead;
	PNODE p = q->pNext;
	if(!pHead)
		return pHead;

	while(p)
	{
		q->pNext = p->pNext;
		p->pNext = pHead;
		pHead = p;
		p = q->pNext;
	}
	
	return pHead;
}
/*
	找出原有链表最大值，断旧链建新链。
*/
# include <stdio.h>
# include <stdlib.h>
# include "link.h"

PNODE SortSeven_Link(PNODE pHead);
void SortBubble_Link(PNODE pHead);
void SortChoice_Link(PNODE pHead);

PNODE SortSeven_Link(PNODE pHead);

int main (void)
{
	PNODE pHead;
	int a[10] = {12,19,56,21,45,32,37,77,61,8};

	pHead = BackwardCreate_Link(a,10);//逆向建链
	ForwardTraversal_Link(pHead);//正向遍历

	pHead = SortSeven_Link(pHead);//选择排序
	ForwardTraversal_Link(pHead);

	return 0;
}

PNODE SortSeven_Link(PNODE pHead)
{
	PNODE pInterim = (PNODE)malloc(sizeof(NODE));
	pInterim->pNext = pHead;
	pHead = pInterim;

	SortChoice_Link(pHead);//调用函数

	pHead = pHead->pNext;
	free(pInterim);

	return pHead;
}

void SortBubble_Link(PNODE pHead)
{
	PNODE p,q,pMin;
	pMin = pHead;

	for(; (q=pMin->pNext)&&(p = q->pNext); pMin = pMin->pNext)
		for(; p; p = q->pNext)
			if(pMin->pNext->data > p->data)
			{
				q->pNext = p->pNext;
				p->pNext = pMin->pNext;
				pMin->pNext = p;
			}
			else
				q = p;
}

void SortChoice_Link(PNODE pHead)
{
	PNODE p,pMin,qMin,pPoint;
	qMin = pPoint = pHead;

	for(; pMin = p = pPoint->pNext; pPoint = pPoint->pNext)
	{
		for(; p->pNext; p = p->pNext)
			if(p->pNext->data < pMin->data)
			{
				qMin = p;
				pMin = p->pNext;
			}

		if(pMin != pPoint->pNext)
		{
			qMin->pNext = pMin->pNext;
			pMin->pNext = pPoint->pNext;
			pPoint->pNext = pMin;
		}
	}
}

/*
	2016年7月24日12:13:11
	逆向建链合并
*/
# include <stdio.h>
# include <stdlib.h>
# include "link.h"

PNODE MergeFour_Link(PNODE pHeadA, PNODE pHeadB);

int main (void)
{
	PNODE pHead = NULL;
	PNODE pHeadA = NULL;
	PNODE pHeadB = NULL;

	int a[18] = {1,1,1,3,6,11,15,22,37,57,61,85,111,112,112,113,113,113};
	int b[12] = {1,1,2,4,6,11,15,32,37,44,68,85};

	printf("链表A:\n");
	pHeadA = FowardCreate_Link(a,18);
	ForwardTraversal_Link(pHeadA);
	printf("链表B:\n");
	pHeadB = FowardCreate_Link(b,12);
	ForwardTraversal_Link(pHeadB);
	printf("合并后:\n");
	pHead = MergeFour_Link(pHeadA,pHeadB);
	ForwardTraversal_Link(pHead);

	return 0;
}

PNODE MergeFour_Link(PNODE pHeadA, PNODE pHeadB)
{
	PNODE pHead = NULL, pTail = NULL, p = NULL;

	while(pHeadA && pHeadB){
		if(pHeadA->data < pHeadB->data){
			p = pHeadA;
			pHeadA = pHeadA->pNext;
		}
		else{
			p = pHeadB;
			pHeadB = pHeadB->pNext;
		}
		if(NULL == pHead)	pTail = pHead = p;
		else if(pTail->data == p->data)	free(p);
		else	pTail = pTail->pNext = p;	
	}
	p = pHeadA = (pHeadB) ?	pHeadB : pHeadA;
	while(pHeadA){
		pHeadA = pHeadA->pNext;
		if(pTail->data == p->data)	free(p);
		else	pTail = pTail->pNext = p;
		p = pHeadA;
	}
	pTail->pNext = NULL;
	return pHead;
}

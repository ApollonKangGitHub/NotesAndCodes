 /*
	2016年9月11日16:25:46
	两非空链表有无相交节点
*/
# include <stdio.h>
# include <stdlib.h>
# include "link.h"

void CreateAdd_Link(PNODE pHead,PNODE pAdd);
PNODE Intersection_Link(PNODE pHeadA,PNODE pHeadB,int *dataA,int *dataB);

int main (void)
{
	PNODE pHead = NULL, pHeadA = NULL, pHeadB = NULL, pHeadC = NULL;
	PNODE Intersect = NULL;
	int dataA=1,dataB=1;

	int a[10] = {11,15,22,7,7,6,8,11,12,13};
	int b[10] = {2,4,6,11,15,2,7,4,8,5};
	int c[5] = {1,8,9,6,5};

	pHeadA = FowardCreate_Link(a,10);
	pHeadB = FowardCreate_Link(b,7);
	pHeadC = FowardCreate_Link(c,4);
	printf("链表A:\n");
	CreateAdd_Link(pHeadA,pHeadC);
	ForwardTraversal_Link(pHeadA);
	printf("链表B:\n");
	CreateAdd_Link(pHeadB,pHeadC);
	ForwardTraversal_Link(pHeadB);

	Intersect = Intersection_Link(pHeadA,pHeadB,&dataA,&dataB);
	if(NULL == Intersect)
		printf("链表A和链表B没有交叉节点");
	else
	{
		printf("链表A和链表B有交叉节点，交叉节点地址为%#X:\n",Intersect);
		printf("交叉结点数据值为：%d\n",Intersect->data);
		printf("该节点是A链表的第%d个节点，是B链表的第%d个节点\n",dataA,dataB);
	}
	return 0;
}

void CreateAdd_Link(PNODE pHead,PNODE pAdd)
{
	PNODE p;
	for(p=pHead;p->pNext;p=p->pNext);
	p->pNext = pAdd;
}

PNODE Intersection_Link(PNODE pHeadA,PNODE pHeadB,int *dataA,int *dataB)
{
	PNODE p, q, point=NULL;
	for(p = pHeadA; p; p=p->pNext,++(*dataA))
		for(q = pHeadB, *dataB=1; q; q=q->pNext,++(*dataB))
			if(p==q)
				return p;
	return p;
}
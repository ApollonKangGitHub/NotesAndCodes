/*
	2016年8月21日15:46:08
	合并两个升序有序链表，并且剔除重复项
*/
# include <stdio.h>
# include <stdlib.h>
# include "link.h"

PNODE MergeThree_Link(PNODE pHeadA, PNODE pHeadB);//合并时剔除重复项  
PNODE MergeNode_Link(PNODE p,PNODE q); 
PNODE MergeFour_Link(PNODE pHeadA, PNODE pHeadB);

int main (void)
{
	PNODE pHeadA = NULL;
	PNODE pHeadB = NULL;//接收链表的头指针
	PNODE pHead = NULL;

	int a[20] = {1,1,3,12,12,23,24,35,101,123,133,133,133,158,200,215,218,219,219,300};
	int b[15] = {1,1,3,9,12,23,25,67,125,125,133,158,200,200,200};

	pHeadA = BackwardCreate_Link(a,20);
	pHeadB = BackwardCreate_Link(b,15);//创建A，B链表

	printf("A链表：");
	ForwardTraversal_Link(pHeadA);
	printf("B链表：");
	ForwardTraversal_Link(pHeadB);//遍历合并前的A，B链表

	pHead = MergeThree_Link(pHeadA,pHeadB);
	//	pHead = MergeFour_Link(pHeadA, pHeadB);
	printf("合并后：");
	ForwardTraversal_Link(pHead);

	return 0;
}

PNODE MergeThree_Link(PNODE pHeadA, PNODE pHeadB)
{
	PNODE pHead = NULL, p = NULL, q = NULL;
	if(!pHeadA || !pHeadB){printf("链表为空，无需合并!!\n"); exit(-1);}
	while(pHeadA && pHeadB)
	{
		(pHeadA->data <= pHeadB->data) ? (p = pHeadA, pHeadA = p->pNext) : (p = pHeadB, pHeadB = p->pNext);//将指针p指向要移动的节点上
		(!pHead) ? (pHead = q = p, p->pNext = NULL) : (q = MergeNode_Link(p,q));
	}
	if(!pHeadA)	pHeadA = pHeadB;
	for(;p = pHeadA; pHeadA = p->pNext,q = MergeNode_Link(p,q));
	return pHead;
}

PNODE MergeNode_Link(PNODE p,PNODE q)
{
	if(!(q->data - p->data))	free(p);//如果尾节点q的数据域与要尾插的p节点数据域相同，就不能再尾插了，而是剔除这个重复值的p节点
	else
	{
		q = q->pNext = p;//指向尾节点的q先与新节点p链接起来，连接起来以后q指向的就不是为节点了。再将q移向尾节点
		p->pNext = NULL;//p为尾节点指针域为NULL
	}
	return q;
}

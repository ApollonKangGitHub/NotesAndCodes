 /*
	2016年7月24日12:13:11
	逆向建链合并
*/
# include <stdio.h>
# include <stdlib.h>
# include "link.h"

PNODE MergeFive_Link(PNODE pHeadA, PNODE pHeadB);

int main (void)
{
	PNODE pHead = NULL;
	PNODE pHeadA = NULL;
	PNODE pHeadB = NULL;

	int a[30] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,6,11,15,22,37,57,61,85,111,112,112,113,113,113};//
	int b[20] = {1,1,1,1,1,1,1,1,1,1,2,4,6,11,15,32,37,44,68,85};//

	printf("链表A:\n");
	pHeadA = FowardCreate_Link(a,30);
	ForwardTraversal_Link(pHeadA);
	printf("链表B:\n");
	pHeadB = FowardCreate_Link(b,20 );
	ForwardTraversal_Link(pHeadB);
	printf("合并后:\n");
	pHead = MergeFive_Link(pHeadA,pHeadB);
	ForwardTraversal_Link(pHead);

	return 0;
}

PNODE MergeFive_Link(PNODE pHeadA, PNODE pHeadB)
{
	PNODE pHead = NULL, pTail = NULL, p = NULL;

	while(pHeadA || pHeadB)
	{
		if(!pHeadB || pHeadA && pHeadA->data < pHeadB->data)
		{
			p = pHeadA;
			pHeadA = pHeadA->pNext;
		}
		else
		{
			p = pHeadB;
			pHeadB = pHeadB->pNext;
		}//先从原链表中删除节点（取出来）
		if(NULL == pHead)//堆头指针判断，如果头指针为空，将取出的节点作为头节点处理
			pTail = pHead = p;
		else if(pTail->data == p->data)//如果头指针不为空，将该节点与新链表为节点数据域进行比较，如果相等直接释放
			free(p);
		else//如果不相等，则进行尾插
			pTail = pTail->pNext = p;	
	}
	pTail->pNext = NULL;
	return pHead;
}

/*
进入while循环则pHeadA与pHeadB不可能都为空。故有四种情况：
	1、pHeadA为空，pHeadB不为空，则p指向pHeadB；
	2、pHeadA不为空，pHeadB不为空且pHeadA->data < pHeadB->data不成立，则p指向pHeadB；
	3、pHeadA不为空，pHeadB为空，则p指向pHeadA；
	4、pHeadA不为空，pHeadB不为空且pHeadA->data < pHeadB->data成立，则p指向pHeadA。
*/
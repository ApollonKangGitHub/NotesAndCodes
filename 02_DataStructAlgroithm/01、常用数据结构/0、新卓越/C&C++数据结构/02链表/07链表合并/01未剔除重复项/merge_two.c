/*
	2016��7��24��12:30:38
	�������ϲ�
*/
# include <stdio.h>
# include <stdlib.h>
# include "link.h"

PNODE MergeTwo_Link(PNODE pHeadA, PNODE pHeadB);
PNODE BackTravInverse_Link(PNODE pHead);

int main (void)
{
	PNODE pHead;
	PNODE pHeadA;
	PNODE pHeadB;

	int a[10] = {1,3,6,11,15,22,37,57,61,85};
	int b[10] = {2,4,6,101,105,302,307,404,608,805};

	printf("����A:\n");
	pHeadA = FowardCreate_Link(a,10);
	ForwardTraversal_Link(pHeadA);
	printf("����B:\n");
	pHeadB = FowardCreate_Link(b,8);
	ForwardTraversal_Link(pHeadB);
	printf("�ϲ���:\n");
	pHead = MergeTwo_Link(pHeadA,pHeadB);
	ForwardTraversal_Link(pHead);

	return 0;
}
/*�������ϲ���*/
PNODE MergeTwo_Link(PNODE pHeadA, PNODE pHeadB)//������������ϲ���һ����������
{
	PNODE pHead = NULL, p = NULL, q = NULL;

	while( pHeadA && pHeadB)
	{
		if(pHeadA->data <= pHeadB->data) 
		{
			p = pHeadA;
			pHeadA = p->pNext;
		}
		else
		{
			p = pHeadB;
			pHeadB = p->pNext;
		}
		p->pNext = NULL;
		if(!pHead) 	q = pHead = p;
		else	q = q->pNext = p;
	}
	if(NULL == pHeadA)
		pHeadA = pHeadB;
	if(pHeadA)
		q->pNext = pHeadA;
	
	return pHead;
}


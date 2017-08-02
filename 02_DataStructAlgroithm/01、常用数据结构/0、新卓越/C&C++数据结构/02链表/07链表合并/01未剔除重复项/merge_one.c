/*
	2016��7��24��12:13:11
	�������ϲ�
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

	printf("����A:\n");
	pHeadA = FowardCreate_Link(a,10);
	ForwardTraversal_Link(pHeadA);
	printf("����B:\n");
	pHeadB = FowardCreate_Link(b,1);
	ForwardTraversal_Link(pHeadB);
	printf("�ϲ���:\n");
	pHead = MergeOne_Link(pHeadA,pHeadB);
	ForwardTraversal_Link(pHead);

	return 0;
}
/*�������ϲ���*/
PNODE MergeOne_Link(PNODE pHeadA, PNODE pHeadB)//������������ϲ���һ����������
{
	PNODE pHead = NULL;
	PNODE p;

	for(; pHeadA || pHeadB; p->pNext = pHead,pHead = p)//�ܹ�����ѭ��pHeadA��pHeadB��������һ����Ϊ��
	{
		if(pHeadB==NULL || (pHeadA && (pHeadA->data <= pHeadB->data)))//����pHeadB��pHeadA����Ϊ�ղ���ִ�������жϣ���������һ��û��������
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
	pHead = BackTravInverse_Link(pHead);//���õ��ú�����ǰ���ϲ�������Ϊ��������
	return pHead;
}
/*���ú���*/
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
/*
	���������ɾ������
	2016��7��21��10:31:20
*/
# include <stdio.h>
# include <stdlib.h>
# include "link.h"

PNODE DeletePos_Link(PNODE pHead,int pos);//ɾ��ָ��λ��pos��Ӧ�Ľڵ�
PNODE DeleteOnlyKey_Link(PNODE pHead,int key);//ɾ��ָ������key��Ӧ�Ľڵ㣨���ظ�ֵ��
PNODE DeleteManyKey_Link(PNODE pHead,int key);//ɾ��ָ������key��Ӧ�Ľڵ㣨���ظ�ֵ��
PNODE DeleteMax_Link(PNODE pHead);//ɾ�����ֵ�ڵ�
PNODE DeleteOdd_Link(PNODE pHead);//ɾ�����������ڵ�

int main (void)
{
	int pos = 0;
	int key = 0;
	int a[10] = {47,47,65,47,47,47,47,47,56,47};
	PNODE pHead;

	pHead = BackwardCreate_Link(a,10);
	ForwardTraversal_Link(pHead);
	printf("\n");

	printf("��������Ҫɾ���Ľڵ�λ��(��pos���ڵ�)��\n");
	scanf("%d",&pos);
	pHead = DeletePos_Link(pHead,pos-1);
	ForwardTraversal_Link(pHead);
	printf("\n");

	printf("��������Ҫɾ��������key��\n");
	scanf("%d",&key);
	pHead = DeleteOnlyKey_Link(pHead,key);
	ForwardTraversal_Link(pHead);
	printf("\n");

	printf("��������Ҫɾ��������key��\n");
	scanf("%d",&key);
	pHead = DeleteManyKey_Link(pHead,key);
	ForwardTraversal_Link(pHead);
	printf("\n");

	pHead = DeleteMax_Link(pHead);
	printf("���ֵɾ���ɹ���ɾ�����Ϊ��\n");
	ForwardTraversal_Link(pHead);
	printf("\n");

	pHead = DeleteOdd_Link(pHead);
	printf("����ɾ����ϣ�ɾ�����Ϊ��\n");
	ForwardTraversal_Link(pHead);
	printf("\n");

	return 0;
}

PNODE DeletePos_Link(PNODE pHead,int pos)
{
	PNODE p,q;
	p = pHead;

	for(pos,p; p && pos; --pos,q=p,p=p->pNext);
	if(!p)
		printf("��Ҫɾ���Ľڵ㳬������Χ��\n");
	else
		(!(pHead-p)) ? (pHead = pHead->pNext) : (q->pNext = p->pNext);

	free(p);

	return pHead;
}

PNODE DeleteOnlyKey_Link(PNODE pHead,int key)
{
	PNODE p,q;
	p = pHead;

	for(p; p && p->data-key; q=p,p=p->pNext);
	if(!p)
		printf("��Ҫɾ����Ԫ�ز��������ڣ�\n");
	else
		(!(pHead-p)) ? (pHead = pHead->pNext) : (q->pNext = p->pNext);


	free(p);

	return pHead;
}

PNODE DeleteManyKey_Link(PNODE pHead,int key)
{
	PNODE p,q;
	p = pHead;

	while(p)
	{
		for(p; p && p->data-key; q=p,p=p->pNext);
		if(!p)
			printf("ɾ����ϣ�\n");
		else
			if(pHead == p)
			{
				pHead = pHead->pNext; 
				free(p);
				p = pHead;
			}
			else
			{
				q->pNext = p->pNext;
				free(p);
				p = q->pNext;
			}
	}
	return pHead;
}

PNODE DeleteMax_Link(PNODE pHead)
{
	PNODE q,pMax,qMax;//p����ʡ��
	pMax = pHead;
	if(pMax == NULL)
	{
		printf("LINK is NULL!\n");
		exit(-1);
	}
	q = pMax;//���е�p��������ǰ��q��ָ�����ʾ����pMax������qMax��ָ�����ʾ

	for(q->pNext; q->pNext; q=q->pNext)
		if(q->pNext->data > pMax->data)
		{
			qMax = q;
			pMax = q->pNext;
		}
	!(pMax-pHead) ?	(pHead = pHead->pNext) : (qMax->pNext = pMax->pNext);

	free(pMax);
	return pHead;
}

PNODE DeleteOdd_Link(PNODE pHead)
{
	PNODE p,q;
	p = pHead;

	while(p)
	{
		for(p; p && ((p->data-1)%2); q=p,p=p->pNext);
		if(!p)
			printf("�����в�����������\n");
		else
			if(pHead == p)
			{
				pHead = pHead->pNext; 
				free(p);
				p = pHead;
			}
			else
			{
				q->pNext = p->pNext;
				free(p);
				p = q->pNext;
			}
	}
	return pHead;
}
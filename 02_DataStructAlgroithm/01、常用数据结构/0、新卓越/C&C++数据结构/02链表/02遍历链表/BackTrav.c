/*
	2016��7��18��11:50:22
*/

# include <stdio.h>
# include <stdlib.h>
# include "link.h"
# define MAX 100

void BackTravEnd_Link(PNODE pHead);
void BackTravArray_Link(PNODE pHead);
PNODE BackTravInverse_Link(PNODE pHead);

int main (void)
{
	PNODE pHead;
	int a[10] = {12,19,56,21,45,32,37,77,61,8};

	printf("�����ɹ�������������Ϊ��\n");
	pHead = BackwardCreate_Link(a,10);
	ForwardTraversal_Link(pHead);

	printf("������������������������������Ϊ��\n");
	BackTravEnd_Link(pHead);
	printf("���������顱�������������������Ϊ��\n");
	BackTravArray_Link(pHead);

	printf("�����������������������������Ϊ��\n");
	pHead = BackTravInverse_Link(pHead);//ÿ����һ�� BackTravInverse_Link()������pHead�������һ���µ�ͷ����ַ
	ForwardTraversal_Link(pHead);
	printf("�����û�ԭ������������������������Ϊ��\n");
	pHead = BackTravInverse_Link(pHead);
	ForwardTraversal_Link(pHead);

	return 0;
}

void BackTravEnd_Link(PNODE pHead)
{
	PNODE pEnd = NULL;
	PNODE p = pHead;

	while(pHead != pEnd)
	{
		for(p; p->pNext != pEnd ; p=p->pNext);
		printf("%-4d",p->data);
		pEnd = p;
		p = pHead;
	}
	printf("\n");
}

void BackTravArray_Link(PNODE pHead)
{
	PNODE p = pHead;
	int i = 0;
	int Temp[MAX] = {0};
	for(p; p; p=p->pNext,++i)
		Temp[i] = p->data;
	for(--i; i>-1; --i)
		printf("%-4d",Temp[i]);

	printf("\n");
	return;
}

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
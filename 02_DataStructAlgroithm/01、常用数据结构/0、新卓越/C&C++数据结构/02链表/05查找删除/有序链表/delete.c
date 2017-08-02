# include <stdio.h>
# include <stdlib.h>
# include "link.h"

void DeleteRepeatKey_link(PNODE pHead);//�޳��������������е��ظ�ֵ
PNODE DeleteAllKey_link(PNODE pHead, int key);////ɾ���������������е�����key

int main (void)
{
	PNODE pHead;
	int key;
	int a[10] = {18,18,20,21,28,31,31,39,44,44};
	pHead = BackwardCreate_Link(a,10);
	ForwardTraversal_Link(pHead);

	printf("������Ҫɾ����key:\n");
	scanf("%d",&key);
	printf("ɾ��Ԫ�ؽ��Ϊ��\n");
	pHead = DeleteAllKey_link(pHead,key);
	ForwardTraversal_Link(pHead);
	printf("\n");

	DeleteRepeatKey_link(pHead);
	ForwardTraversal_Link(pHead);
	printf("\n");

	return 0;
}

PNODE DeleteAllKey_link(PNODE pHead, int key)
{
	PNODE p = pHead;
	PNODE q;

	for(p; p && (p->data-key); q=p,p=p->pNext);

	for(;p == pHead && p && !(p->data-key); free(p),p=pHead)
		pHead = pHead->pNext;
	for(;p != pHead && p && !(p->data-key);	free(p),p=q->pNext)
		q->pNext = p->pNext;

	return pHead;
}

void DeleteRepeatKey_link(PNODE pHead)
{
	
	PNODE p,q;
	p = pHead;
	q = p->pNext;

	if(pHead == NULL)
	{
		printf("����Ϊ�գ�����ɾ����ν�ظ���!\n");
		exit(-1);
	}

	for(;q;q = p->pNext)
		if(p->data == q->data)
		{
			p->pNext = q->pNext;
			free(q);	
		}
		else
			p = q;

	printf("�޳��ظ�ֵ�Ժ������Ϊ:\n");
}


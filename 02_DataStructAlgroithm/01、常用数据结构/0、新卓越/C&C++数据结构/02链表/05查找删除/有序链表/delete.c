# include <stdio.h>
# include <stdlib.h>
# include "link.h"

void DeleteRepeatKey_link(PNODE pHead);//剔除升序有序链表中的重复值
PNODE DeleteAllKey_link(PNODE pHead, int key);////删除升序有序链表中的所有key

int main (void)
{
	PNODE pHead;
	int key;
	int a[10] = {18,18,20,21,28,31,31,39,44,44};
	pHead = BackwardCreate_Link(a,10);
	ForwardTraversal_Link(pHead);

	printf("请输入要删除的key:\n");
	scanf("%d",&key);
	printf("删除元素结果为：\n");
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
		printf("链表为空，无需删除所谓重复项!\n");
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

	printf("剔除重复值以后的链表为:\n");
}


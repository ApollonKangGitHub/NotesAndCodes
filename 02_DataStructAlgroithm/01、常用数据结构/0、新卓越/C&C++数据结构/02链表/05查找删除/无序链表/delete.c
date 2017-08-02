/*
	无序链表的删除操作
	2016年7月21日10:31:20
*/
# include <stdio.h>
# include <stdlib.h>
# include "link.h"

PNODE DeletePos_Link(PNODE pHead,int pos);//删除指定位置pos对应的节点
PNODE DeleteOnlyKey_Link(PNODE pHead,int key);//删除指定数据key对应的节点（无重复值）
PNODE DeleteManyKey_Link(PNODE pHead,int key);//删除指定数据key对应的节点（有重复值）
PNODE DeleteMax_Link(PNODE pHead);//删除最大值节点
PNODE DeleteOdd_Link(PNODE pHead);//删除所有奇数节点

int main (void)
{
	int pos = 0;
	int key = 0;
	int a[10] = {47,47,65,47,47,47,47,47,56,47};
	PNODE pHead;

	pHead = BackwardCreate_Link(a,10);
	ForwardTraversal_Link(pHead);
	printf("\n");

	printf("请输入您要删除的节点位置(第pos个节点)：\n");
	scanf("%d",&pos);
	pHead = DeletePos_Link(pHead,pos-1);
	ForwardTraversal_Link(pHead);
	printf("\n");

	printf("请输入您要删除的数据key：\n");
	scanf("%d",&key);
	pHead = DeleteOnlyKey_Link(pHead,key);
	ForwardTraversal_Link(pHead);
	printf("\n");

	printf("请输入您要删除的数据key：\n");
	scanf("%d",&key);
	pHead = DeleteManyKey_Link(pHead,key);
	ForwardTraversal_Link(pHead);
	printf("\n");

	pHead = DeleteMax_Link(pHead);
	printf("最大值删除成功，删除结果为：\n");
	ForwardTraversal_Link(pHead);
	printf("\n");

	pHead = DeleteOdd_Link(pHead);
	printf("奇数删除完毕，删除结果为：\n");
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
		printf("您要删除的节点超出链表范围！\n");
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
		printf("您要删除的元素不在链表内！\n");
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
			printf("删除完毕！\n");
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
	PNODE q,pMax,qMax;//p可以省略
	pMax = pHead;
	if(pMax == NULL)
	{
		printf("LINK is NULL!\n");
		exit(-1);
	}
	q = pMax;//所有的p可以用其前驱q的指针域表示，而pMax不能用qMax的指针域表示

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
			printf("链表中不存在奇数！\n");
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
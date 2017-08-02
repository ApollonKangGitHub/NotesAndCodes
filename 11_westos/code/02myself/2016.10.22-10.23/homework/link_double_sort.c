/*
 *双向链表排序
 *
 * */
# include<stdio.h>
# include<stdlib.h>

typedef struct Node{
	int data;
	struct Node * pPre;//前驱指针
	struct Node * pNext;//后继指针
}NODE;

NODE * New_node();//创建一个新的节点
NODE * Create(int);//创建双向链表
NODE * Sort(NODE *);//排序
void Print(NODE * pHead);//遍历


int main(void)
{
	int key = 0;
	int num = 0;
	NODE * pHead = NULL;
	printf("Please input number of link_node:\n");
	scanf("%d",&num);
	pHead = Create(num);
	Print(pHead);

	pHead = Sort(pHead);
	Print(pHead);

	return 0;
}
NODE * New_node()
{
	int data;
	printf("Please input your number of node:\n");
	scanf("%d",&data);

	NODE * pNew = (NODE *)malloc(sizeof(NODE));
	pNew->data = data;
	pNew->pNext = NULL;
	pNew->pPre = NULL;
	
	return pNew;
}
NODE * Create(int num)
{
	NODE * pHead = NULL, * pNew = NULL, * pTail = NULL;
	int i, data;

	printf("The number of node is %d!\n",num);
	for(i=0; i<num; i++)
	{
		pNew = New_node();
		if(!pHead)
			pTail = pHead = pNew;
		else{
			pNew->pPre = pTail;
			pTail = pTail->pNext = pNew;
		}
	}
	return pHead;
}

NODE * Sort(NODE * pHead)
{
	NODE * pHeadNew, * p, * pMin, * pTail;
	pTail = pHeadNew = NULL;
	p = pMin = pHead;

	while(pHead)
	{
		for(; p && (!(pMin->data > p->data) || (pMin = p)); p = p->pNext);//Trval Link And Find Min Node

		if(pMin == pHead){
			if(pHead->pNext){
				pHead->pNext->pPre = NULL;
				pHead = pHead->pNext;
			}
			else	
				pHead = NULL;
		}
		else{
			pMin->pPre->pNext = pMin->pNext;
			if(pMin->pNext)
				pMin->pNext->pPre = pMin->pPre;
		}
		pMin->pPre = pMin->pNext = NULL;

		if(!pHeadNew)	
			pTail = pHeadNew = pMin;
		else{
			pMin->pPre = pTail;
			pTail = pTail->pNext = pMin;
		}
		p = pMin = pHead;	
	}
	return pHeadNew;
}
void Print(NODE * pHead)
{
	NODE * p = pHead;
	for(p;p;p=p->pNext)
		printf("%d\t",p->data);

	printf("\n");
}


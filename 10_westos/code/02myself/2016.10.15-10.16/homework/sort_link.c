# include<stdio.h>
# include<stdlib.h>
# include<time.h>

typedef struct Node{
	int data;
	struct Node * pNext;
}NODE;

NODE * Create(int);//创建链表
NODE * Sort_Link(NODE *);//链表排序
void Print(NODE * pHead);//链表遍历

int main (void)
{
	int n;
	NODE * pHead = NULL;
	printf("请输入产生随机数的个数:\n");
	scanf("%d",&n);
	pHead = Create(n);
	printf("产生的随机数创建链表为：\n");
	Print(pHead);

	pHead = Sort_Link(pHead);
	printf("排序后的链表为：\n");
	Print(pHead);
	return 0;
}

NODE * Create(int n)
{
	if(!n){
		printf("链表为空！\n");
		return NULL;
	}
	int i;
	NODE * pHead = NULL;
	NODE * pNew = NULL;
	srand(time(NULL));

	for(i = 0; i<n; i++)
	{
		pNew = (NODE *)malloc(sizeof(NODE));
		if(NULL == pNew)
		{
			printf("内存分配失败！\n");
			exit(EXIT_FAILURE);
		}
		pNew->data = rand()%15-5;
		pNew->pNext = pHead;
		pHead = pNew;
	}
	return pHead;
}

NODE * Sort_Link(NODE * pHead)
{
	if(!pHead){
		printf("链表为空！\n");
		exit(EXIT_FAILURE);
	}
	NODE * pHeadNew = NULL;//新的链表头节点
	NODE * p, * q;//用来遍历链表
	NODE * pMax, * qMax;//用来存放最大直节点与最大值之前的节点的地址

	while(pHead)
	{
		qMax = NULL;
		q = pMax = pHead;
		p = q->pNext;
		for(;p; q=p, p=p->pNext)
		{
			if(p->data > pMax->data){
				qMax = q;
				pMax = qMax->pNext;
		 	}
		}
		if(NULL == qMax){
			pHead = pHead->pNext;
		}
		else{
			qMax->pNext = pMax->pNext;
		}
		pMax->pNext = pHeadNew;
		pHeadNew = pMax;
	}
	return pHeadNew;
}
void Print(NODE * pHead)
{
	NODE * p = pHead;
	for(; p; p = p->pNext)
		printf("%-4d", p->data);
	printf("\n");
}



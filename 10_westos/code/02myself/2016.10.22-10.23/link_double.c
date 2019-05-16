# include<stdio.h>
# include<stdlib.h>

typedef struct Node{
	int data;
	struct Node * pPre;//前驱指针
	struct Node * pNext;//后继指针
}NODE;

NODE * New_node();//创建一个单独的、新的、双向链表的节点
NODE * Create(int);//创建双向链表
NODE * Sort(NODE *);//排序
void Insert_key_next(NODE *,int);//后插入
NODE * Insert_key_pre(NODE *,int);//前插入
void Print(NODE * pHead);//遍历


int main(void)
{
	int key = 0;
	NODE * pHead = NULL;
	pHead = Create(5);
	Print(pHead);

//	Sort(pHead);
//	printf("请输入key（key必须在链表中）:\n");
//	scanf("%d",&key);
//	Insert_key_next(pHead,key);
//	pHead = Insert_key_pre(pHead,key);

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
		if(pHead == NULL)
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
	NODE * pHeadNew = NULL;
	NODE * p = pHead;
	NODE * pMin = pHead;
	NODE * pTail = pHeadNew;

	while(pHead)
	{
		for(p;p;p=p->pNext)
			if(pMin->data > p->data)
				pMin = p;

		if(pMin == pHead){
			pHead->pNext->pPre = NULL;
			pHead = pHead->pNext;
		}
		else if(pMin->pNext == NULL){
			pMin->pPre->pNext = NULL;
		}
		else{
			pMin->pPre->pNext = pMin->pNext;
			pMin->pNext->pPre = pMin->pPre;
		}
		pMin->pPre = pMin->pNext = NULL;

		if(pHeadNew == NULL){
			pTail = pHeadNew = pMin;
		}
		else{
			pMin->pPre = pTail;
			pTail->pNext = pMin;
			pTail = pMin;
		}
		p = pMin = pHead;	
	}
	return pHeadNew;
}
/*后插入法*/
void Insert_key_next(NODE * pHead,int key)
{
	NODE * pNew = New_node();
	NODE * p = pHead;
	for(p; p && (p->data != key); p=p->pNext);

	if(p == NULL){
		printf("没有该数据，插入失败！\n");
		exit(EXIT_FAILURE);
	}

	pNew->pPre = p;
	pNew->pNext = p->pNext;
	p->pNext = pNew;
	if(pNew->pNext != NULL)
		pNew->pNext->pPre = pNew;
	
}
/*前插入法*/
NODE * Insert_key_pre(NODE * pHead,int key)
{
	NODE * pNew = New_node();
	NODE * p = pHead;

	for(p; p && (p->data != key); p=p->pNext);
	if(p == NULL){
		printf("没有该数据，插入失败！\n");
		exit(EXIT_FAILURE);
	}

	if(p == pHead){
		pNew->pNext = pHead;
		pHead = pHead->pPre = pNew;
	}
	else{
		pNew->pNext = p;
		pNew->pPre = p->pPre;
		p->pPre->pNext = pNew;
		p->pPre = pNew;
	
	}
	return pHead;
}
void Print(NODE * pHead)
{
	NODE * p = pHead;
	for(p;p;p=p->pNext)
		printf("%d\t",p->data);

	printf("\n");
}


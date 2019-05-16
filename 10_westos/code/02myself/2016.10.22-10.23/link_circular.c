# include<stdio.h>
# include<stdlib.h>

typedef struct Node{
	int data;
	struct Node * pNext;
}NODE;
NODE * Joseph(NODE * pHead,int len);
NODE * Create_circular(int num);
void Print_circular(NODE * pHead);

int main(void)
{
	int num, len;
	printf("请输入要生成的链表节点个数（大于1)：");
	scanf("%d",&num);
	NODE * pHead = NULL;
	pHead = Create_circular(num);
	Print_circular(pHead);
	
	printf("请输入约瑟夫环的删除长度len（大于1）:");
	scanf("%d",&len);
	pHead = Joseph(pHead,len);
	Print_circular(pHead);
}

NODE * Create_circular(int num)
{
	int i = 0;
	NODE *pNew, *pTail = NULL, *pHead = NULL;
	for(i=0; i<num; i++)
	{
		pNew = (NODE*)malloc(sizeof(NODE));	
		pNew->data = i+1;
		pNew->pNext = NULL;

		if(pHead == NULL){
			pNew->pNext = pNew;
			pTail = pHead = pNew;
		}
		else{
			pNew->pNext = pHead;
			pTail = pTail->pNext = pNew;
		}
	}
	return pHead;
}
NODE * Joseph(NODE * pHead,int len)
{
	NODE * p = pHead, * q = NULL;
	int i = 0;
	while(p->pNext != p)
	{		
		for(i=1; i<len; i++, q=p, p=p->pNext);
		q->pNext = p->pNext;
		printf("delete %d\n",p->data);
		free(p);
		p=q->pNext;	
	}
	return p;
}

void Print_circular(NODE * pHead)
{
	NODE * pTrav = pHead;
	do{
		printf("%d\t",pTrav->data);
		pTrav = pTrav->pNext;
	}while(pTrav != pHead);
	printf("\n");
}


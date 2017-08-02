/**
 *
 *用单向循环链表实现约瑟夫环
 *num为链表节点个数（约瑟夫环元素个数）
 *len为约瑟夫环的删除元素的间距
 *从1开始数到len，删除第len个，再从1开始重复以上步骤
 *直到删除至只剩一个节点
 *输出该剩余的节点
 */
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
	printf("Please input your JESEPH's Node num(num>1,eg:7):\n");
	scanf("%d",&num);
	NODE * pHead = NULL;
	pHead = Create_circular(num);
	Print_circular(pHead);
	
	printf("Please input your JOSEPH's delete len(len>1,eg:3):\n");
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


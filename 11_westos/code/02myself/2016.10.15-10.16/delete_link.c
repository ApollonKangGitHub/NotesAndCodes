# include<stdio.h>
# include<stdlib.h>
# include<time.h>

typedef struct Node{
	int data;
	struct Node * pNext;
}NODE;

NODE * Create(int n)
{
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
		pNew->data = rand()%5 + 10;
		pNew->pNext = pHead;
		pHead = pNew;
	}
	return pHead;
}

void DeleteRepeatKey_link(NODE * pHead)
{
	NODE * pOne = pHead;
	NODE * pFind = NULL;
	NODE * qFind = NULL;
	if(!pHead)
	{
		printf("链表为空！\n");
		exit(EXIT_FAILURE);
	}

	for(pOne;pOne;pOne = pOne->pNext)//for(pOne;pOne->pNext;pOne = pOne->pNext)烦人的BUG
	{
		qFind = pOne;
		pFind = qFind->pNext;
		for(;pFind;){
			if(pOne->data-pFind->data){
				qFind = pFind;
				pFind = pFind->pNext;
			}
			else{
				qFind->pNext = pFind->pNext;
				free(pFind);
				pFind = qFind->pNext;
			}
		}
	}
}
void Print(NODE * pHead)
{
	NODE * p = pHead;
	for(p;p;p=p->pNext)
		printf("%-4d",p->data);
	printf("\n");
}

int main (void)
{
	int n;
	NODE * pHead = NULL;
	printf("请输入产生随机数的个数:\n");
	scanf("%d",&n);
	pHead = Create(n);
	Print(pHead);

	DeleteRepeatKey_link(pHead);

	Print(pHead);
	return 0;
}

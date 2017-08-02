/*
	2016��7��18��11:01:04
	
	�κ�һ��������֮ǰ��Ȼ���ڣ�����һ��������
	�������µĽڵ�֮ǰpHead = NULL.��ͷָ��Ϊ���ޣ���ָ��
	

*/

# include <stdio.h>
# include <stdlib.h>

typedef struct Node
{
	int data;
	struct Node * pNext;
}NODE,*PNODE;

PNODE FowardCreate_Link(int * a,int length);
PNODE BackwardCreate_Link(int * a,int length);
void ForwardTraversal_Link(PNODE pHead);


PNODE FowardCreate_Link(int * a,int length)
{
	PNODE pTail;
	PNODE pHead = NULL;
	int i = 0;

	for(i = 0; i < length; ++i)
	{
		PNODE pNew = (PNODE)malloc(sizeof(NODE));
		if(NULL == pNew)
		{
			printf("CREATE LINK IS FAIL!\n");
			exit(-1);
		}

		pNew->data = a[i];//�������������
		pNew->pNext = NULL;//��Ϊβ�ڵ�ָ����ΪNULL

		if(NULL == pHead)
			pTail = pHead = pNew;
		else
			pTail = pTail->pNext = pNew;
	}
	return pHead;
}

PNODE BackwardCreate_Link(int * a,int length)
{
	PNODE pHead = NULL;
	int i;
	for(i = length-1; i > -1; --i)
	{
		PNODE pNew = (PNODE)malloc(sizeof(NODE));
		if(NULL == pNew)
		{
			printf("CREATE LINK IS FAIL!\n");
			exit(-1);
		}
		pNew->data = a[i];//�������������
		pNew->pNext = pHead;
		pHead = pNew;
	}
	return pHead;
}

void ForwardTraversal_Link(PNODE pHead)
{
	PNODE p;
	p = pHead;

	if(NULL == pHead)
		printf("LINK IS EMPTY!\n");
	else
		for(p; p; p=p->pNext)
			printf("%-4d",p->data);
	printf("\n");
}

int main (void)
{
	PNODE pHead;
	int a[8] = {1,2,3,4,5,6,7,8};
	pHead = BackwardCreate_Link(a,8);
	ForwardTraversal_Link(pHead);

	return 0;
}
# include<stdio.h>
# include<stdlib.h>
# define LEN 8 
# define MAX 20

typedef struct Node{
	int data;
	struct Node * pNext;
}NODE;

NODE * Create_Link(NODE *);//¿¿¿¿¿¿¿¿¿¿¿
void Circluar_Link(NODE *);//¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿
void Print_Link(NODE *);//¿¿¿¿
NODE * Decide_Link(NODE *);//
NODE * Decide_Link_Esay(NODE *);
int Len_Circluar_Link(NODE *);//¿¿¿¿¿
int Len_Link(NODE *, NODE *);//¿¿¿¿¿¿¿

NODE * Create_Link(NODE * pHead)
{
	NODE * pNew = NULL;
	int i = 0;
	for(i; i<LEN; i++)
	{
		pNew = (NODE*)malloc(sizeof(NODE));
		pNew->data = LEN - i;
		pNew->pNext = NULL;

		pNew->pNext = pHead;
		pHead = pNew;
	}	
	return pHead;
}
void Circluar_Link(NODE * pHead)
{
	NODE * p = pHead;
	for(p;p->pNext;p=p->pNext);
	p->pNext = pHead;//->pNext->pNext;
}

void Print_Link(NODE * pHead)	
{
	NODE * p = pHead;
	for(p; p; p = p->pNext)
		printf("%d\t",p->data);
}

NODE * Decide_Link(NODE * pHead)
{
	int i,j;

	NODE * p = pHead;
	NODE * q;
	NODE * arr[MAX];

	for(p,i=0;p;p=p->pNext,i++)
	{
		arr[i] = p;
		for(j=0,q=p->pNext;j<i;j++)
			if(arr[j] == q)
				return q;
	}
	return NULL;
}


int Len_Circluar_Link(NODE * pCircluar)
{
	int len = 1;
	NODE * p = pCircluar;
	while(p->pNext != pCircluar){
		p=p->pNext;
		len++;
	}
	return len;
	
}

int Len_Link(NODE *pHead, NODE * pCircluar)
{
	int len1=0,len2=0;
	NODE * p = pHead;
	while(p != pCircluar){
		p = p->pNext;
		len1++;
	}
	len2 = Len_Circluar_Link(pCircluar);

	return (len1+len2);
}
int main(void)
{
	NODE * pHead = NULL;
	NODE * pCircluar = NULL;
	pHead = Create_Link(pHead);
	Print_Link(pHead);
	printf("\n");
	Circluar_Link(pHead);

	pCircluar = Decide_Link(pHead);
	//pCircluar = Decide_Link_Esay(pHead);
	if(pCircluar == NULL)
		printf("No have circluar!\n");
	else
		printf("Have circluar!\n");

	printf("The length of circluar is %d\n",Len_Circluar_Link(pCircluar));
	printf("The node_data of circluar is %d\n",pCircluar->data);
	printf("Thew length of link is %d\n",Len_Link(pHead,pCircluar));

	return 0;
}

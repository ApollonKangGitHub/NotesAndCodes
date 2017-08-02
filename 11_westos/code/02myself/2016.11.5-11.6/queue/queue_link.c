# include<stdio.h>
# include<string.h>
# include<stdlib.h>

typedef struct Node{
	int data;
	struct Node * pNext;
}NODE;

typedef struct Queue{
	NODE * pFront;
	NODE * pRear;
}QUEUE;

void init_queue(QUEUE * pQ)
{
	pQ->pFront = NULL;
	pQ->pRear = NULL;
}
void input_queue(QUEUE * pQ)
{
	int data = 0;
	NODE * pNew = (NODE *)malloc(sizeof(NODE));
	if(NULL == pNew){
		printf("�ڴ����ʧ�ܣ�\n");
		exit(EXIT_FAILURE);
	}
	printf("���������Ԫ�أ�");
	scanf("%d",&data);
	pNew->data = data;
	pNew->pNext = NULL;

	if(pQ->pRear == NULL)
		pQ->pFront = pQ->pRear = pNew;
	else
		pQ->pRear = pQ->pRear->pNext = pNew;
}

NODE * output_queue(QUEUE * pQ)
{
	NODE * tmp = pQ->pFront;
	if(pQ->pFront == NULL){
		printf("����Ϊ�գ�\n");
		exit(EXIT_FAILURE);
	}
	pQ->pFront = pQ->pFront->pNext;
	tmp->pNext = NULL;

	return tmp;
}
int main(void)
{
	NODE * tmp = NULL;
	QUEUE Q;
	init_queue(&Q);
	input_queue(&Q);
	tmp = output_queue(&Q);
//	tmp = output_queue(&Q);

	printf("����Ԫ��%d\n",tmp->data);
	return 0;
}

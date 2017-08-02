# include <stdio.h>
#include <malloc.h>
#define LEN	6

typedef struct Queue
{
	int * pBase;//动态分配存储空间
	int front;//头指针
	int rear;//尾指针

}QUEUE;

void init(QUEUE *);//初始化
bool en_queue(QUEUE *, int val);//插入
void traverse_queue(QUEUE *);//遍历
bool full_queue(QUEUE *);//是否满
bool out_queue(QUEUE *,int *);//出队
bool emput_queue(QUEUE *);//是否空

int main (void)
{
	QUEUE Q;
	int val;
	
	init(&Q);
	en_queue(&Q,1);
	en_queue(&Q,2);
	en_queue(&Q,3);
	en_queue(&Q,4);
	en_queue(&Q,5);
	en_queue(&Q,6);
	en_queue(&Q,7);

	traverse_queue(&Q);

	if( out_queue(&Q,&val) )
	{
		printf("出队成功，队列出队的元素是：%d\n",val);
	}
	else
	{
		printf("出队失败!\n");
	}
	traverse_queue(&Q);

	return 0;
}

/*初始化函数*/
void init(QUEUE *pQ)
{
	pQ->pBase = (int *)malloc(sizeof(int) * LEN);//分配存储空间可存储6个元素
	pQ->front = 0;
	pQ->rear = 0;
}

bool en_queue(QUEUE * pQ,int val)
{
	if( full_queue(pQ) )
		return false;
	else
	{
		pQ->pBase[pQ->rear] = val;
		pQ->rear = (pQ->rear + 1) % LEN;

		return true;
	}
	
}

bool full_queue(QUEUE * pQ)
{
	if((pQ->rear + 1) % LEN == pQ->front)
		return true;
	else
		return false;
}

void traverse_queue(QUEUE * pQ)
{
	int i = pQ->front;

	while(i != pQ->rear)
	{
		printf("%d ",pQ->pBase[i]);
		i = (i+1) % LEN;
	}

	printf("\n");
	return;
}

bool out_queue(QUEUE *pQ,int * pVal)
{
	if ( emput_queue(pQ) )
		return false;
	else
	{
		*pVal = pQ->pBase[pQ->front];
		pQ->front = (pQ->front + 1) % LEN;

		return true;
	}

}

bool emput_queue(QUEUE * pQ)
{
	if(pQ->front == pQ->rear)
		return true;
	else
		return false;
}
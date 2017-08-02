# include<stdio.h>
# include<stdlib.h>

typedef struct Arr
{
	int num;
	int data;
	struct Arr * pNext;
}ARR,*PARR;

PARR Sort_ArrToLink(int *a,int len);
void Print_Arr(int *a,int len);
void Sort_Num(PARR pHead);
void Sort_LinkToArr(int *a,int len,PARR pHead);

int main(void)
{
	PARR pHead = NULL;
	int arr[19] = {1,2,2,3,3,3,4,4,5,5,5,5,6,6,6,7,8,9,10};

	Print_Arr(arr,19);//����
	pHead = Sort_ArrToLink(arr,19);//������Ԫ���У���ͬ��С��Ԫ������ֵ(data)�����(num)Ϊһ���ڵ㣬��ŵ�������
	Sort_Num(pHead);//��������ÿ���ڵ��numֵ����������
	Sort_LinkToArr(arr,19,pHead);//������������Ԫ�ؽ���Sort_ArrToLink()�ķ������
	Print_Arr(arr,19);//����

	return 0;
}
void Print_Arr(int *a,int len)
{
	int i;
	for(i=0;i<len;++i)
		printf("%d  ",a[i]);
	printf("\n");
}
PARR Sort_ArrToLink(int *a,int len)
{
	int i,j;
	PARR pTail,pHead,pNew;
	pHead = (PARR)malloc(sizeof(ARR));
	pHead->pNext = NULL;
	pTail = pHead;
	for(i=0; i<len; i=j+1)
	{
		for(j=i; j<len && (a[j]==a[j+1]); ++j);
		pNew = (PARR)malloc(sizeof(ARR));
		pNew->num = j-i+1;
		pNew->data = a[j];
		pNew->pNext = pTail->pNext;
		pTail = pTail->pNext = pNew;
	}
	return pHead;
}
void Sort_Num(PARR pHead)
{
	PARR q,pMove;
	int point = 1;
	for(q=pHead->pNext,point;q->pNext->pNext;q=q->pNext,++point);
	while(point)
	{
		for(q=pHead;q->pNext->pNext;q=q->pNext)
			if(q->pNext->num < q->pNext->pNext->num)
			{
				pMove = q->pNext;
				q->pNext = pMove->pNext;
				pMove->pNext = q->pNext->pNext;
				q->pNext->pNext = pMove;
			}
		--point;
	}
}
void Sort_LinkToArr(int *a,int len,PARR pHead)
{
	PARR p = NULL;
	int i=0,j=0;
	for(p=pHead->pNext;p;p=p->pNext)
		for(i,j=0;i<len && (j<p->num); ++i,++j)
			a[i] = p->data;
}
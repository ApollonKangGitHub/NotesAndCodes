# include <stdio.h>
# include <stdlib.h>
# include "link.h"

void SwapMaxNodeOne_Link(PNODE pHead);
int main (void)
{
	PNODE pHead;
	int a[10] = {12,19,56,21,45,32,37,77,61,8};

	pHead = BackwardCreate_Link(a,10);//������
	ForwardTraversal_Link(pHead);//�������

	SwapMaxNodeOne_Link(pHead);
	ForwardTraversal_Link(pHead);

	return 0;
}

void SwapMaxNodeOne_Link(PNODE pHead)
{
	PNODE pMax = pHead, p = pHead->pNext;
	int data = pHead->data;
	while(p)
	{
		if(pMax->data < p->data)	pMax = p;
		p = p->pNext;
	}
	if(pMax == pHead)
	{
		printf("���ֵΪͷ��㣬���ý���");
		exit(-1);
	}
	pHead->data = pMax->data;	
	pMax->data = data;

}


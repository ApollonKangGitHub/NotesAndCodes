/*
	2016��8��24��11:02:54�޸�
	�����.cpp�ļ�����λ��������.c�ļ���Ҫ��ԭ�е�bool���ͻ���int��
	����#define true��false�ſ�������C��C++�Ĳ������Ĵ���
*/
# include <stdio.h>
# include <stdlib.h>
# include "link.h"
# define false 0
# define true 1

int AscendingOrder_Link(PNODE pHead);//�����ж�
int DescendingOrder_Link(PNODE pHead);//�����ж�

int main (void)
{
	PNODE pHead;
	int a[10] = {18,18,20,21,28,31,31,39,44,44};
	pHead = BackwardCreate_Link(a,10);
	ForwardTraversal_Link(pHead);

	if(AscendingOrder_Link(pHead))
		printf("��������!\n");
	else
		printf("��������!\n");

	if(DescendingOrder_Link(pHead))
		printf("��������!\n");
	else
		printf("��������!\n");

	return 0;
}

int AscendingOrder_Link(PNODE pHead)
{
	PNODE p = pHead;
	for(p; p->pNext; p=p->pNext)
		if(p->data > p->pNext->data)
			return false;
	return true;
}


int DescendingOrder_Link(PNODE pHead)
{
	PNODE p = pHead;
		for(p; p->pNext; p=p->pNext)
			if(p->data < p->pNext->data)
				return false;
		return true;
}

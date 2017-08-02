/*
	�ҳ�ԭ���������ֵ���Ͼ�����������
*/
# include <stdio.h>
# include <stdlib.h>
# include "link.h"

PNODE SortSix_Link(PNODE pHead);

int main (void)
{
	PNODE pHead;
	int a[10] = {12,19,56,21,45,32,37,77,61,8};

	pHead = BackwardCreate_Link(a,10);//������
	ForwardTraversal_Link(pHead);//�������

	pHead = SortSix_Link(pHead);//ѡ������
	ForwardTraversal_Link(pHead);

	return 0;
}

PNODE SortSix_Link(PNODE pHead)
{
	PNODE p, q, pMax, qMax, pHeadnew;
	pHeadnew = NULL;

	for(; q = pMax = pHead; pMax->pNext = pHeadnew,pHeadnew = pMax)
	{	
		p = q->pNext;
		for(p; p; q = p,p=p->pNext)
			if(p->data > pMax->data)
			{
				pMax = p;
				qMax = q;
			}
		if(pMax == pHead)	pHead = pHead->pNext;
		else	qMax->pNext = pMax->pNext;
	}
	return pHeadnew;
}
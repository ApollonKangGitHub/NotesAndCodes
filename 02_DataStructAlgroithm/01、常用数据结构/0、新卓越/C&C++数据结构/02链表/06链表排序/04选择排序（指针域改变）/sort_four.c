# include <stdio.h>
# include <stdlib.h>
# include "link.h"

PNODE SortFour_Link(PNODE pHead);
int main (void)
{
	int a[10] = {12,17,65,32,24,98,11,6,56,47};
	PNODE pHead;
	pHead = BackwardCreate_Link(a,10);
	ForwardTraversal_Link(pHead);

	pHead = SortFour_Link(pHead);
	ForwardTraversal_Link(pHead);

	return 0;
}
PNODE SortFour_Link(PNODE pHead)
{
	PNODE p,q,pMin,qMin,pPoint,qPoint;
	pPoint = pHead;

	for(;(pMin = q = pPoint)&&(p = q->pNext); qPoint = pPoint,pPoint = pPoint->pNext)
	{	
		for(; p; q = p,p = q->pNext)
			if(p->data < pMin->data)
			{
				qMin = q;
				pMin = p;
			}
		if(pMin != pPoint)
		{
			qMin->pNext = pMin->pNext;
			pMin->pNext = pPoint;
			if(pPoint == pHead)	pPoint = pHead = pMin;
			else	qPoint->pNext = pPoint = pMin;
		}
	}
	return pHead;
}

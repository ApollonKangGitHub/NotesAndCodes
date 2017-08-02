# include <stdio.h>
# include <stdlib.h>
# include "link.h"

PNODE SortTwo_Link(PNODE pHead);
int main (void)
{
	int a[10] = {12,17,65,32,24,98,11,6,56,47};
	PNODE pHead;
	pHead = BackwardCreate_Link(a,10);
	ForwardTraversal_Link(pHead);

	pHead = SortTwo_Link(pHead);
	ForwardTraversal_Link(pHead);

	return 0;
}
PNODE SortTwo_Link(PNODE pHead)
{
	PNODE p,q,pMin,qMin;
	pMin = pHead;

	for(pMin; (q = pMin) && (p = q->pNext); qMin = pMin,pMin = pMin->pNext)
		for(p; p; p=p->pNext)
			if(pMin->data > p->data)
			{
				q->pNext = p->pNext;
				p->pNext = pMin;
				if(pMin == pHead)	pMin = pHead = p;
				else	qMin->pNext = pMin = p;
			}
			else
				q = p;
	return pHead;
}
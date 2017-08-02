# include <stdio.h>
# include <stdlib.h>
# include "link.h"

void SortOne_Link(PNODE pHead);

int main (void)
{
	PNODE pHead;
	int a[10] = {12,19,56,21,45,32,37,77,61,8};

	pHead = BackwardCreate_Link(a,10);//逆向建链
	ForwardTraversal_Link(pHead);//正向遍历

	SortOne_Link(pHead);//冒泡排序
	ForwardTraversal_Link(pHead);

	return 0;
}

void SortOne_Link(PNODE pHead)
{
	PNODE p = pHead;
	PNODE q;

	for(p; p; p=p->pNext)
		for(q=p; q; q=q->pNext)
			if(p->data > q->data)
			{
				int temp = p->data;
				p->data = q->data;
				q->data = temp;
			}
}
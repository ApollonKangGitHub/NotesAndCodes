/*
	2016��7��17��15:37:56	
*/
# include <stdio.h>
# include <stdlib.h>
# include "link.h"

void DeletepIn_link(PNODE p);
int main (void)
{
	int a[8] = {3,2,7,6,9,5,10,8};
	PNODE pHead;
	pHead = FowardCreate_Link(a,8);
	ForwardTraversal_Link(pHead);

	DeletepIn_link(pHead->pNext->pNext);//�������������Ĳ���ͷָ��
	ForwardTraversal_Link(pHead);

	return 0;
}

/*
ɾ��δ֪ͷָ�룬ȴ֪�����м�һ���ڵ�ĵ�ַ��pInָ��ýڵ㣩�����ɾ���ýڵ㣿
*/
void DeletepIn_link(PNODE pIn)
{
	PNODE pDel = pIn->pNext;
	int temp = pIn->data;
	pIn->data = pDel->data;
	pDel->data = temp;
	pIn->pNext = pDel->pNext;
	free(pDel);

	printf("ɾ������λ�ýڵ���Ϊ:\n");
}
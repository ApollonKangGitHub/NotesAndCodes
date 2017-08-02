/*
	2016��8��21��15:46:08
	�ϲ����������������������޳��ظ���
*/
# include <stdio.h>
# include <stdlib.h>
# include "link.h"

PNODE MergeThree_Link(PNODE pHeadA, PNODE pHeadB);//�ϲ�ʱ�޳��ظ���  
PNODE MergeNode_Link(PNODE p,PNODE q); 
PNODE MergeFour_Link(PNODE pHeadA, PNODE pHeadB);

int main (void)
{
	PNODE pHeadA = NULL;
	PNODE pHeadB = NULL;//���������ͷָ��
	PNODE pHead = NULL;

	int a[20] = {1,1,3,12,12,23,24,35,101,123,133,133,133,158,200,215,218,219,219,300};
	int b[15] = {1,1,3,9,12,23,25,67,125,125,133,158,200,200,200};

	pHeadA = BackwardCreate_Link(a,20);
	pHeadB = BackwardCreate_Link(b,15);//����A��B����

	printf("A����");
	ForwardTraversal_Link(pHeadA);
	printf("B����");
	ForwardTraversal_Link(pHeadB);//�����ϲ�ǰ��A��B����

	pHead = MergeThree_Link(pHeadA,pHeadB);
	//	pHead = MergeFour_Link(pHeadA, pHeadB);
	printf("�ϲ���");
	ForwardTraversal_Link(pHead);

	return 0;
}

PNODE MergeThree_Link(PNODE pHeadA, PNODE pHeadB)
{
	PNODE pHead = NULL, p = NULL, q = NULL;
	if(!pHeadA || !pHeadB){printf("����Ϊ�գ�����ϲ�!!\n"); exit(-1);}
	while(pHeadA && pHeadB)
	{
		(pHeadA->data <= pHeadB->data) ? (p = pHeadA, pHeadA = p->pNext) : (p = pHeadB, pHeadB = p->pNext);//��ָ��pָ��Ҫ�ƶ��Ľڵ���
		(!pHead) ? (pHead = q = p, p->pNext = NULL) : (q = MergeNode_Link(p,q));
	}
	if(!pHeadA)	pHeadA = pHeadB;
	for(;p = pHeadA; pHeadA = p->pNext,q = MergeNode_Link(p,q));
	return pHead;
}

PNODE MergeNode_Link(PNODE p,PNODE q)
{
	if(!(q->data - p->data))	free(p);//���β�ڵ�q����������Ҫβ���p�ڵ���������ͬ���Ͳ�����β���ˣ������޳�����ظ�ֵ��p�ڵ�
	else
	{
		q = q->pNext = p;//ָ��β�ڵ��q�����½ڵ�p�������������������Ժ�qָ��ľͲ���Ϊ�ڵ��ˡ��ٽ�q����β�ڵ�
		p->pNext = NULL;//pΪβ�ڵ�ָ����ΪNULL
	}
	return q;
}

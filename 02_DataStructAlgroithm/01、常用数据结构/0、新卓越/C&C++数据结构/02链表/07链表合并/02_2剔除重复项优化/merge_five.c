 /*
	2016��7��24��12:13:11
	�������ϲ�
*/
# include <stdio.h>
# include <stdlib.h>
# include "link.h"

PNODE MergeFive_Link(PNODE pHeadA, PNODE pHeadB);

int main (void)
{
	PNODE pHead = NULL;
	PNODE pHeadA = NULL;
	PNODE pHeadB = NULL;

	int a[30] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,6,11,15,22,37,57,61,85,111,112,112,113,113,113};//
	int b[20] = {1,1,1,1,1,1,1,1,1,1,2,4,6,11,15,32,37,44,68,85};//

	printf("����A:\n");
	pHeadA = FowardCreate_Link(a,30);
	ForwardTraversal_Link(pHeadA);
	printf("����B:\n");
	pHeadB = FowardCreate_Link(b,20 );
	ForwardTraversal_Link(pHeadB);
	printf("�ϲ���:\n");
	pHead = MergeFive_Link(pHeadA,pHeadB);
	ForwardTraversal_Link(pHead);

	return 0;
}

PNODE MergeFive_Link(PNODE pHeadA, PNODE pHeadB)
{
	PNODE pHead = NULL, pTail = NULL, p = NULL;

	while(pHeadA || pHeadB)
	{
		if(!pHeadB || pHeadA && pHeadA->data < pHeadB->data)
		{
			p = pHeadA;
			pHeadA = pHeadA->pNext;
		}
		else
		{
			p = pHeadB;
			pHeadB = pHeadB->pNext;
		}//�ȴ�ԭ������ɾ���ڵ㣨ȡ������
		if(NULL == pHead)//��ͷָ���жϣ����ͷָ��Ϊ�գ���ȡ���Ľڵ���Ϊͷ�ڵ㴦��
			pTail = pHead = p;
		else if(pTail->data == p->data)//���ͷָ�벻Ϊ�գ����ýڵ���������Ϊ�ڵ���������бȽϣ�������ֱ���ͷ�
			free(p);
		else//�������ȣ������β��
			pTail = pTail->pNext = p;	
	}
	pTail->pNext = NULL;
	return pHead;
}

/*
����whileѭ����pHeadA��pHeadB�����ܶ�Ϊ�ա��������������
	1��pHeadAΪ�գ�pHeadB��Ϊ�գ���pָ��pHeadB��
	2��pHeadA��Ϊ�գ�pHeadB��Ϊ����pHeadA->data < pHeadB->data����������pָ��pHeadB��
	3��pHeadA��Ϊ�գ�pHeadBΪ�գ���pָ��pHeadA��
	4��pHeadA��Ϊ�գ�pHeadB��Ϊ����pHeadA->data < pHeadB->data��������pָ��pHeadA��
*/
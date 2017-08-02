/*
	2016��7��19��14:59:52
*/
# include <stdio.h>
# include <stdlib.h>
# include "link.h"

typedef struct Code
{
	int num_code;//�ڵ����
	int odd_code;//��������
	int even_code;//ż������
	int max_code;//���ֵ
}CODE,*PCODE;

PCODE Statistics_Link(PNODE pHead);

int main (void)
{
	PNODE pHead = NULL;
	PCODE pNum = NULL;
	int a[10] = {12,19,56,21,45,32,37,77,61,8};

	pHead = FowardCreate_Link(a,10);
	ForwardTraversal_Link(pHead);

	pNum = Statistics_Link(pHead);
	printf("����������%d��\nż��������%d��\n�ڵ�������%d��\n���Ԫ��Ϊ��%d\n",pNum->odd_code,pNum->even_code,pNum->num_code,pNum->max_code);

	return 0;
}
PCODE Statistics_Link(PNODE pHead)
{
	PNODE p = pHead;
	PCODE pNum = (PCODE)malloc(sizeof(CODE));
	/*�����ڸú������������������ڸú���������������Ȼ������������ڴ��ͷţ��Ҳ���pNUm��ַ���г���*/
	int max = pHead->data;
	int odd_code = 0;
	int even_code = 0;

	for(p; p; p=p->pNext)
	{
		if(p->data%2 == 0)
			even_code++;
		else
			odd_code++;

		if(max < p->data)
			max = p->data;
	}
	pNum->max_code = max;
	pNum->even_code = even_code;
	pNum->odd_code = odd_code;
	pNum->num_code = even_code + odd_code;

	return pNum;
}

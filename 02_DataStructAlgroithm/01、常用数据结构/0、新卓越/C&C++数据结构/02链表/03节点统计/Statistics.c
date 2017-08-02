/*
	2016年7月19日14:59:52
*/
# include <stdio.h>
# include <stdlib.h>
# include "link.h"

typedef struct Code
{
	int num_code;//节点个数
	int odd_code;//奇数个数
	int even_code;//偶数个数
	int max_code;//最大值
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
	printf("奇数个数：%d个\n偶数个数：%d个\n节点总数：%d个\n最大元素为：%d\n",pNum->odd_code,pNum->even_code,pNum->num_code,pNum->max_code);

	return 0;
}
PCODE Statistics_Link(PNODE pHead)
{
	PNODE p = pHead;
	PCODE pNum = (PCODE)malloc(sizeof(CODE));
	/*必须在该函数内输出结果，必须在该函数内输出结果，不然函数调用完毕内存释放，找不到pNUm地址运行出错。*/
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

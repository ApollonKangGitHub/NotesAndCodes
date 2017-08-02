# include <stdio.h>
# include <stdlib.h>

typedef struct Node
{
	int data;
	struct Node * pNext;
}NODE,* PNODE;

typedef struct Stack
{
	PNODE pTop;
	PNODE pBottom;
}STACK,* PSTACK;

void init_stack(PSTACK);//建栈
void push_stack(PSTACK,int);//压栈
void traverse_stack(PSTACK);
bool empty_stack(PSTACK pS);
bool pop_stack(PSTACK,int *);//出栈
void clear_stack(PSTACK pS);

int main (void)
{
	STACK S;//STACK 等价于 struct Stack
	int val;

	init_stack(&S);
	push_stack(&S,1);
	push_stack(&S,2);
	push_stack(&S,3);
	push_stack(&S,4);
	push_stack(&S,5);
	traverse_stack(&S);

	
	//clear_track(&S);//清空

	if( pop_stack(&S,&val) )
	{
		printf("出栈成功，出栈的元素是%d\n",val);
	}
	else
	{
		printf("出栈失败！\n");
	}
	traverse_stack(&S);


	return 0;
}
/*创建一个栈*/
void init_stack(PSTACK pS)
{
	pS->pTop = (PNODE)malloc(sizeof(NODE));
	if(NULL == pS->pTop)
	{
		printf("动态内存分配失败!\n");
		exit(-1);	
	}
	else
	{
		pS->pBottom = pS->pTop;
		pS->pTop->pNext = NULL;//pS->pBottom->pNext = NULL;也可以
	}
}

void push_stack(PSTACK pS,int val)
{
	PNODE pNew = (PNODE)malloc(sizeof(NODE));
	pNew->data = val;
	pNew->pNext = pS->pTop;//不可以写成pNew->pNext = pS->pBottom
	pS->pTop = pNew;

	return;
}

void traverse_stack(PSTACK pS)
{
	PNODE p = pS->pTop;
	
	while (p != pS->pBottom)
	{
		printf("%d ",p->data);
		p = p->pNext;
	}
	printf("\n");

	return;
}

bool empty_stack(PSTACK pS)
{
	if(pS->pTop == pS->pBottom)
		return true;
	else
		return false;
}
//把pS所指向的栈出栈，并把出栈的元素存入pVal形参所指向的变量中
bool pop_stack(PSTACK pS,int *pVal)
{
	if(empty_stack(pS))//pS本身存放的就是S的地址
	{
		return false;
	}
	else
	{
		PNODE r = pS->pTop;
		*pVal = r->data;
		pS->pTop = r->pNext;
		free(r);
		r = NULL;

		return true;
	}
}

void clear_stack(PSTACK pS)
{
	if(empty_stack(pS))
		return;
	else
	{
		PNODE p = pS->pTop;
		PNODE q = NULL;

		while(p != pS->pBottom)
		{
			q = p->pNext;
			free(p);
			p = q;
		}
		pS ->pTop = pS->pBottom;
	}

}
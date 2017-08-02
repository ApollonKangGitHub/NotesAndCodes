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

void init_stack(PSTACK);//��ջ
void push_stack(PSTACK,int);//ѹջ
void traverse_stack(PSTACK);
bool empty_stack(PSTACK pS);
bool pop_stack(PSTACK,int *);//��ջ
void clear_stack(PSTACK pS);

int main (void)
{
	STACK S;//STACK �ȼ��� struct Stack
	int val;

	init_stack(&S);
	push_stack(&S,1);
	push_stack(&S,2);
	push_stack(&S,3);
	push_stack(&S,4);
	push_stack(&S,5);
	traverse_stack(&S);

	
	//clear_track(&S);//���

	if( pop_stack(&S,&val) )
	{
		printf("��ջ�ɹ�����ջ��Ԫ����%d\n",val);
	}
	else
	{
		printf("��ջʧ�ܣ�\n");
	}
	traverse_stack(&S);


	return 0;
}
/*����һ��ջ*/
void init_stack(PSTACK pS)
{
	pS->pTop = (PNODE)malloc(sizeof(NODE));
	if(NULL == pS->pTop)
	{
		printf("��̬�ڴ����ʧ��!\n");
		exit(-1);	
	}
	else
	{
		pS->pBottom = pS->pTop;
		pS->pTop->pNext = NULL;//pS->pBottom->pNext = NULL;Ҳ����
	}
}

void push_stack(PSTACK pS,int val)
{
	PNODE pNew = (PNODE)malloc(sizeof(NODE));
	pNew->data = val;
	pNew->pNext = pS->pTop;//������д��pNew->pNext = pS->pBottom
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
//��pS��ָ���ջ��ջ�����ѳ�ջ��Ԫ�ش���pVal�β���ָ��ı�����
bool pop_stack(PSTACK pS,int *pVal)
{
	if(empty_stack(pS))//pS�����ŵľ���S�ĵ�ַ
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
/**
	*2016年12月13日10:52:39
	*Create Stack of Link
**/
#include <stdio.h>
#include <stdlib.h>

#ifndef bool
#define bool int

typedef struct stack_node{
	int data;
	struct stack_node * pNext;
}STACKNODE;/*栈的节点结构体*/

typedef struct stack_link{
	STACKNODE * pTop;
	STACKNODE * pBottom;
}STACKLINK; /*栈顶指针与栈底指针结构体*/

enum{false,true};

void init_stack(STACKLINK *);/*初始化*/
void push_stack(STACKLINK *);/*压栈*/
void travsal_stack(STACKLINK *);/*遍历*/
void pop_stack(STACKLINK *);/*出栈*/
bool empty_stack(STACKNODE * pS);/*栈判空，链式栈不存在满栈情况，无需判满*/

int main(void)
{
	STACKLINK Stack;
	init_stack(&Stack);/*初始化栈*/

	push_stack(&Stack);/*压栈*/
	travsal_stack(&Stack);/*从栈顶开始遍历*/

	pop_stack(&Stack);/*出栈*/
	travsal_stack(&Stack);

	return 0;
}

void init_stack(STACKLINK * pS)
{
	pS->pTop = NULL;
	pS->pBottom = NULL;/*初始化将栈顶指针与栈底指针均赋空*/
	printf("初始化成功!\n");
}

void push_stack(STACKLINK * pS)
{
	int num, choose;
	STACKNODE * pNew = NULL;
	while(1){
		printf("请输入压栈数据:");
		scanf("%d",&num);
		
		pNew = (STACKNODE *)malloc(sizeof(STACKNODE));
		if(NULL == pNew){
			printf("内存分配失败!\n");
			exit(EXIT_FAILURE);
		}
		pNew->data = num;
		pNew->pNext = NULL;

		if(empty_stack(pS->pTop) == -1){/*栈为空*/
			pS->pBottom = pS->pTop = pNew;
		}
		else{/*栈不为空*/
			pNew->pNext = pS->pTop;
			pS->pTop = pNew;
		}
		
		printf("继续压栈？（继续请选1，结束请选2）:");
		scanf("%d",&choose);
		if(choose != 1){
			break;
		}
	}
}

void travsal_stack(STACKLINK * pS)
{
	STACKNODE * pMove;
	pMove = pS->pTop;

	while(1){
		if(pMove == NULL){
			break;
		}
		printf("%d\t",pMove->data);
		pMove = pMove->pNext;
	}
	printf("\n");
}

void pop_stack(STACKLINK * pS)
{
	STACKNODE * pDelete;
	int choose = 0;
	while(1){
		pDelete = pS->pTop;
		if(empty_stack(pDelete) == -1){
			printf("栈为空，出栈失败!\n");
			exit(EXIT_FAILURE);
		}
		printf("出栈元素为：%d\n",pDelete->data);
		pS->pTop = pDelete->pNext;
		pDelete->pNext = NULL;
		free(pDelete);

		printf("继续出栈？（继续请选1，结束请选2）:");
		scanf("%d",&choose);
		if(choose != 1){
			break;
		}
	}
}

bool empty_stack(STACKNODE * pN)
{
	return ((pN == NULL) ? -1 : 0);
}
#endif









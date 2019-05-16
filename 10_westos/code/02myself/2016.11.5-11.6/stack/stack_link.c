/**
	*2016��12��13��10:52:39
	*Create Stack of Link
**/
#include <stdio.h>
#include <stdlib.h>

#ifndef bool
#define bool int

typedef struct stack_node{
	int data;
	struct stack_node * pNext;
}STACKNODE;/*ջ�Ľڵ�ṹ��*/

typedef struct stack_link{
	STACKNODE * pTop;
	STACKNODE * pBottom;
}STACKLINK; /*ջ��ָ����ջ��ָ��ṹ��*/

enum{false,true};

void init_stack(STACKLINK *);/*��ʼ��*/
void push_stack(STACKLINK *);/*ѹջ*/
void travsal_stack(STACKLINK *);/*����*/
void pop_stack(STACKLINK *);/*��ջ*/
bool empty_stack(STACKNODE * pS);/*ջ�пգ���ʽջ��������ջ�������������*/

int main(void)
{
	STACKLINK Stack;
	init_stack(&Stack);/*��ʼ��ջ*/

	push_stack(&Stack);/*ѹջ*/
	travsal_stack(&Stack);/*��ջ����ʼ����*/

	pop_stack(&Stack);/*��ջ*/
	travsal_stack(&Stack);

	return 0;
}

void init_stack(STACKLINK * pS)
{
	pS->pTop = NULL;
	pS->pBottom = NULL;/*��ʼ����ջ��ָ����ջ��ָ�������*/
	printf("��ʼ���ɹ�!\n");
}

void push_stack(STACKLINK * pS)
{
	int num, choose;
	STACKNODE * pNew = NULL;
	while(1){
		printf("������ѹջ����:");
		scanf("%d",&num);
		
		pNew = (STACKNODE *)malloc(sizeof(STACKNODE));
		if(NULL == pNew){
			printf("�ڴ����ʧ��!\n");
			exit(EXIT_FAILURE);
		}
		pNew->data = num;
		pNew->pNext = NULL;

		if(empty_stack(pS->pTop) == -1){/*ջΪ��*/
			pS->pBottom = pS->pTop = pNew;
		}
		else{/*ջ��Ϊ��*/
			pNew->pNext = pS->pTop;
			pS->pTop = pNew;
		}
		
		printf("����ѹջ����������ѡ1��������ѡ2��:");
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
			printf("ջΪ�գ���ջʧ��!\n");
			exit(EXIT_FAILURE);
		}
		printf("��ջԪ��Ϊ��%d\n",pDelete->data);
		pS->pTop = pDelete->pNext;
		pDelete->pNext = NULL;
		free(pDelete);

		printf("������ջ����������ѡ1��������ѡ2��:");
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









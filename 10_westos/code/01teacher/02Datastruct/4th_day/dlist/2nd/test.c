#include "test.h"

Node* create(Node* phead, int data)
{
	Node* tmp = malloc(sizeof(Node));
	tmp->data = data;
	tmp->pre = NULL;
	tmp->next = NULL;
	Node* find = phead;

	if(phead == NULL)	
		;
	else {
		tmp->next = phead;
		phead->pre = tmp;
	}

	return tmp;
}
void show(Node* phead)
{
	while(phead){
		printf("%d\t", phead->data);
		phead = phead->next;
	}
	printf("\n");
}
void insert(Node* phead, int data, int key)
{
	Node* tmp = malloc(sizeof(Node));
	tmp->data = data;
	tmp->pre = NULL;
	tmp->next = NULL;
	Node* find = phead;

	while(find->data != key)	
		find = find->next;
	tmp->next = find->next;
	tmp->pre = find;
	find->next = tmp;
	if(tmp->next != NULL)
		tmp->next->pre = tmp;
}









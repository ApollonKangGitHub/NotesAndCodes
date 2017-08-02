#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int data;
	struct node* pre;
	struct node* next;
}Node;

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
Node* insert(Node* phead, int data, int key)
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
int main()
{
	Node* head = NULL;

	head = create(head, 12);
	head = create(head, 102);
	head = create(head, 32);
	head = create(head, 42);
	head = create(head, 19);
	show(head);
	insert(head, 100, 12);
	show(head);

	return 0;
}











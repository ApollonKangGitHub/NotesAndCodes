#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int data;
	struct node* next;
}Node;

void show(Node* phead)
{
	while(phead){
		printf("%d\t", phead->data);
		phead = phead->next;
	}
	printf("\n");
}
Node* create(Node* phead, int d)
{
	Node* tmp = malloc(sizeof(Node));
	tmp->data = d;
	tmp->next = NULL;
	Node* find = phead;

	if(phead == NULL)
		phead = tmp;
	else {
		while(find->next != NULL)
			find = find->next;
		find->next = tmp;
	}
	return phead;
}
void insert(Node* phead, int data, int key)
{
	Node* tmp = malloc(sizeof(Node));
	tmp->data = data;
	tmp->next = NULL;

	Node* find = phead;
	while(find->data != key)
		find = find->next;
	tmp->next = find->next;
	find->next = tmp;
}
Node* insert_head(Node* phead, int data)
{
	Node* tmp = malloc(sizeof(Node));
	tmp->data = data;
	tmp->next = NULL;

	tmp->next = phead;
	return tmp;	
}
int main()
{
	Node* head = NULL;
	
	head = create(head, 400);
	create(head, 200);
	create(head, 100);
	create(head, 300);
	show(head);

	insert(head, 270, 300);	
	show(head);
	head = insert_head(head, 330);
	show(head);

	return 0;
}






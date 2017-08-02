#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int data;
	struct node* next;
}Node;
void show(Node* phead)
{
	Node* find = phead->next;

	do{
		printf("%d\t", find->data);
		find = find->next;

	}while(phead->next != find);

	printf("\n");
}
Node* create(Node* phead, int data)
{
	Node* tmp = malloc(sizeof(Node));
	tmp->data = data;
	tmp->next = NULL;
	Node* find = phead->next;
	
	if(phead->next == NULL){
		phead->next = tmp;
		tmp->next = tmp;
	}
	else {
		while(find->next != phead->next)	
			find = find->next;		
		tmp->next = phead->next; 
		find->next = tmp;
	
	}
	return phead;	
}
Node* insert(Node* phead, int data, int key)
{
	Node* tmp = malloc(sizeof(Node));
	tmp->data = data;
	tmp->next = NULL;
	Node* find = phead->next;

	while(find->data != key)
		find = find->next;

	tmp->next = find->next;
	find->next = tmp;
	return phead;
}
Node* init_node(Node* phead)
{
	Node* tmp = malloc(sizeof(Node));
	tmp->next = NULL;

	return tmp;
}
int main()
{
	Node* head = NULL;
	head = init_node(head);
	head = create(head, 20);
	head = create(head, 10);
	head = create(head, 30);
	head = create(head, 14);
	head = create(head, 16);
	show(head);	

	head = insert(head, 50, 14);
	head = insert(head, 500, 16);
	show(head);	

	return 0;
}








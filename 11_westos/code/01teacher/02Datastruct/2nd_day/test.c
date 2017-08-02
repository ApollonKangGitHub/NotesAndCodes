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
Node* pre_insert(Node* phead, int data, int key )
{
	Node* tmp = malloc(sizeof(Node));
	tmp->data = data;
	tmp->next = NULL;
	Node* find = phead;
	
	if(phead->data == key){
		tmp->next = phead;
		phead = tmp;
	}
	else {
		while(find->next != NULL && find->next->data != key )	
			find = find->next;
		if(find->next != NULL){
			tmp->next = find->next;
			find->next = tmp;
		}
		else {
			printf("Not found key! \n");
		}
	}
	return phead;
}
int main()
{
	Node* head = NULL;
	
	head = create(head, 400);
	create(head, 200);
	create(head, 100);
	create(head, 300);
	create(head, 33);
	create(head, 43);
	show(head);
	
	head = pre_insert(head, 55, 400);
	show(head);

	return 0;
}











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
Node* del(Node* phead, int key)
{
	Node* find = phead;
	Node* tmp = NULL;

	if(find->data == key){
		phead = phead->next;
		free(find);
		find = NULL;
	}
	else {
		while(find->next != NULL && find->next->data != key)
			find = find->next;
		if(find->next != NULL){
			tmp = find->next;		
			find->next = tmp->next;
			free(tmp);		
			tmp = NULL;
		}
		else {
			printf("Not found key!\n");
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
	head = del(head, 43);	
	show(head);

	return 0;
}











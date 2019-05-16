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
Node* sort(Node* phead)
{
	Node* min = phead;
	Node* pre_min = phead;
	Node* find = phead;
	Node* newhead = NULL;
	Node* newtail = NULL;
	
	while(phead){
		min = find = phead;
		while(find->next != NULL){
			//  1st step:    find min          
			if(min->data > find->next->data){
				pre_min = find;
				min = find->next;
			}
			find = find->next;
		}
			//   2nd step:    del  min
		if(min == phead){
			phead = phead->next;
			min->next = NULL;
		}
		else {
			pre_min->next = min->next;
			min->next = NULL;
			printf("min: %d\n", min->data);
		}
			// 3rd step:    insert min
		if(newhead == NULL){
			newtail = newhead = min;
//			newtail = min;
		}
		else {
			newtail->next = min;
			newtail = newtail->next;
		}
	}
	
	return newhead;
}
void del_repeat(Node* phead)
{
	Node* find = phead;
	Node* tmp = phead;
	Node* pk = phead;
	Node* k = NULL;

	while(pk->next != NULL){
		find = pk;
		tmp = pk;
		while(tmp->next != NULL){
			if(find->data == tmp->next->data){		
				k = tmp->next;
				tmp->next = k->next;
				free(k);	
				k = NULL;
			}
			else 
				tmp = tmp->next;
				
		}
		pk = pk->next;
	}	
}
//----------------------------------------------------------
void callback( void (*p_del_repeat)(Node*),  Node* phead)
{
	p_del_repeat(phead);
} 
int main()
{
	Node* head = NULL;
	
	head = create(head, 400);
	create(head, 20);
	create(head, 10);
	create(head, 300);
	create(head, 33);
	create(head, 33);
	create(head, 3);
	create(head, 20);
	create(head, 43);
	create(head, 33);
	create(head, 10);
	show(head);

//	del_repeat(head);
	callback(del_repeat, head);
	show(head);

//	Node* newhead = sort(head);	
//	show(newhead);

	return 0;
}











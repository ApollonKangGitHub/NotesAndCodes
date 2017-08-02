#include "test.h"

void show(Node* phead)
{
	while(phead){
		printf("%d\t", phead->num);
		phead = phead->next;
	}
	printf("\n");
}
Node* create(Node* phead, int d)
{
	Node* tmp = malloc(sizeof(Node));
	tmp->num = d;
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
Node* pre_insert(Node* phead, int num, int key )
{
	Node* tmp = malloc(sizeof(Node));
	tmp->num = num;
	tmp->next = NULL;
	Node* find = phead;
	
	if(phead->num == key){
		tmp->next = phead;
		phead = tmp;
	}
	else {
		while(find->next != NULL && find->next->num != key )	
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










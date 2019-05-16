#include <stdio.h>
#include <stdlib.h>

struct sta_node{
	int data;
	struct sta_node* next;
};
struct link_sta{
	struct sta_node* top;
	struct sta_node* buttom;
}; 

int init_link_sta(struct link_sta* ls)
{
	ls->top = NULL;
	ls->buttom = NULL;
}
void in_link_sta(struct link_sta* ls, int value)
{
	struct sta_node* tmp = malloc(sizeof(struct sta_node));
	tmp->data = value;
	tmp->next = NULL;

	if(ls->top == NULL){
		ls->top = tmp;
		tmp->next = ls->buttom; 
	}
	else{
		tmp->next = ls->top;
		ls->top = tmp;
	}
}
struct sta_node* if_empty(struct link_sta* ls)
{
	if(ls->top == ls->buttom){
		printf("stack is empty. \n");
		return NULL;
	}
}
struct sta_node* out_link_sta(struct link_sta* ls)
{
	if(!(if_empty(ls)))
		return NULL;
	else {
		struct sta_node* tmp = ls->top;
		ls->top = (ls->top)->next;
		tmp->next = NULL;

		return tmp;	
	}
}
int main()
{
	struct link_sta LS;
	init_link_sta(&LS);	
	
	in_link_sta(&LS, 10);
	in_link_sta(&LS, 12);

	struct sta_node* value = out_link_sta(&LS);
//	value = out_link_sta(&LS);
//	value = out_link_sta(&LS);
//	value = out_link_sta(&LS);
	if(value == NULL){
		exit(1);
	}
	printf("value: %d\n", value->data);

	return 0;
}











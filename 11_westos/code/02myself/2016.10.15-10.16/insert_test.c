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
Node * delete_node_key(Node* phead,int key)
{
	Node * p = phead;
	Node *q = NULL;

	for(p;p && (p->data != key); q=p,p=p->next);
	if(p == NULL){
		printf("Not found!No have this key!\n");
		exit(EXIT_FAILURE);
	}
	if(p == phead){
		phead = phead->next;
	}
	else{
		q->next = p->next;
	}
	free(p);
	p = NULL;
	
	return phead;
}
Node * insert_before(Node * phead,int data,int key)
{
	Node* tmp = malloc(sizeof(Node));
	tmp->data = data;
	tmp->next = NULL;

	Node *p = phead;
	Node *q = NULL;
	for(p,q; p && (p->data != key);q = p,p = p->next);

	if(NULL == p){
		q->next = tmp;
		printf("No have this key!Can't to insert!So we put this node at last.\n");
	}
	if(p == phead){
		tmp->next = phead;
		phead = tmp;
	}
	else{
		tmp->next = p;
		q->next = tmp;
	}

	return phead;
}
int main()
{
	Node* head = NULL;
	int key = 0,data = 0;

	head = create(head, 400);
	create(head, 200);
	create(head, 100);
	create(head, 300);
	show(head);
#if 0
/*insert*/
	printf("Please input your data and key，between space:\n");
	scanf("%d%d",&data,&key);
	head = insert_before(head, data, key);
	show(head);
#endif
#if 1
/*delete*/
	printf("Please input the key of you want to delete:\n");
	scanf("%d",&key);
	head = delete_node_key(head,key);
	show(head);
#endif
	return 0;
}



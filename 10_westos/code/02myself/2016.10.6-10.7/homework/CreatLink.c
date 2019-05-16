#include <stdio.h>
#include <stdlib.h>

struct node{
	int data;
	struct node* next;
};
void show(struct node* phead)
{
	while(phead){
		printf("%d\t", phead->data);
		phead = phead->next;
	}
	printf("\n");
}
struct node* create(struct node* phead, int d)
{
	struct node* p;
	struct node* tmp = malloc(sizeof(struct node));
	tmp->data = d;
	tmp->next = NULL;

	if(phead == NULL)
		return tmp;
	else {
		for(p=phead;p->next;p=p->next);
		tmp->next=p->next;
		p->next=tmp;
	//	phead->next = tmp；
	/*
		每次新增加的节点链接在了phead之后
		而不是尾节点之后
		中间的节点就与头指针断了联系
	*/			
	}
}
int main()
{
	struct node* head = NULL;
	
	head = create(head, 400);
	create(head, 300);
	create(head, 200);
	create(head, 100);

	show(head);

	return 0;
}






#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node* next;
};

struct link_que{
	struct node* front;
	struct node* rear;
};

int init_queue(struct link_que* lq)
{
	lq->front = NULL;
	lq->rear = NULL;
}
void in_queue(struct link_que * lq, int data)
{
	struct node* tmp = malloc(sizeof(struct node));
	tmp->data = data;
	tmp->next = NULL;
	
	if(lq->rear == NULL){
		lq->rear = tmp;
		lq->front = tmp;
	}
	else {
		lq->rear->next = tmp;
		lq->rear = tmp;
	}
}
struct node* out_queue(struct link_que* lq)
{
	if(lq->front == NULL){
		printf("queue is empty. \n");	
		return NULL;
	}
	else {
		struct node* tmp = lq->front;
		lq->front = lq->front->next;
		tmp->next = NULL;
		
		return tmp;
	}
}
int main()
{
	struct link_que LQ;
	
	init_queue(&LQ);		
	
	in_queue(&LQ, 11);
	in_queue(&LQ, 12);
	struct node* tmp = out_queue(&LQ);
	printf("tmp->data: %d\n", tmp->data);
	tmp = out_queue(&LQ);
	printf("tmp->data: %d\n", tmp->data);

	tmp = out_queue(&LQ);
	if(tmp == NULL){
		exit(1);
	}
	printf("tmp->data: %d\n", tmp->data);

	return 0;
}












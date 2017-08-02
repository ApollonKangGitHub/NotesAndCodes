#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define		SIZE	5

struct que{
	int data[SIZE];
	int front;
	int rear;
};

int init_queue(struct que* q)
{
	memset(q->data, 0, sizeof(q->data));
	q->front = 0;
	q->rear = 0;
}
int in_queue(struct que* q, int data)
{
	  	
	
	if((q->rear + 1)%SIZE == q->front){
		printf("full queue. \n");
		exit(1);
	}
	else {
		(q->rear)++;
		q->rear = (q->rear)%SIZE;
		q->data[q->rear] = data;
	}
}

int out_queue(struct que* q)
{
	if(q->front == q->rear){
		printf("queue is empty. \n");
		exit(1);
	}
	else {
		(q->front)++;
		q->front = (q->front)%SIZE;
		int tmp = q->data[q->front];

		return tmp;	
	}
}
int main()
{
	struct que Q;
	init_queue(&Q);	
	in_queue(&Q, 11);
	in_queue(&Q, 12);
	in_queue(&Q, 13);
	in_queue(&Q, 14);
	int ret = out_queue(&Q);
	//printf("ret: %d\n", ret);

	ret = out_queue(&Q);
	//printf("ret: %d\n", ret);

	ret = out_queue(&Q);
	//printf("ret: %d\n", ret);

	in_queue(&Q, 16);
	in_queue(&Q, 17);

	ret = out_queue(&Q);
	ret = out_queue(&Q);
	ret = out_queue(&Q);
	printf("ret: %d\n", ret);

	ret = out_queue(&Q);
	printf("ret: %d\n", ret);


#if 0
	printf(" %d\n", Q.data[0]);
	printf(" %d\n", Q.data[1]);
	printf(" %d\n", Q.data[2]);
	printf(" %d\n", Q.data[3]);
	ret = out_queue(&Q);
	ret = out_queue(&Q);

	in_queue(&Q, 14);
	in_queue(&Q, 15);
	in_queue(&Q, 16);
	in_queue(&Q, 16);
	int ret = out_queue(&Q);
	ret = out_queue(&Q);
	printf("ret: %d\n", ret);
	ret = out_queue(&Q);
	printf("ret: %d\n", ret);
	ret = out_queue(&Q);
	printf("ret: %d\n", ret);
#endif
	return 0;
}





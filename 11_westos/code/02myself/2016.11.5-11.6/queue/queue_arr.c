# include<stdio.h>
# include<string.h>
# include<stdlib.h>

# define SIZE 5
typedef struct queue{
	int data[SIZE];
	int front;
	int rear;
}QUEUE;

void init_queue(QUEUE *);
void input_queue(QUEUE *);
void output_queue(QUEUE *);

void init_queue(QUEUE *pQ){
	pQ->front = 1;
	pQ->rear = 2;
	memset(pQ->data, 0, sizeof(pQ->data));
}

void input_queue(QUEUE * pQ)
{
	if(pQ->rear == pQ->front){
		printf("队列已满！不能再入队\n");
		return;
	}
	printf("请输入队列元素:\n");
	scanf("%d",&(pQ->data[pQ->rear]));//先入队再移rear
	pQ->rear = (pQ->rear+1)%SIZE;
}

void output_queue(QUEUE * pQ)
{
	if((pQ->front + 1) % SIZE == pQ->rear){
		printf("队列为空！不能再出队！\n");
		return;
	}
	pQ->front = (pQ->front+1) % SIZE;//先移front再出队
	printf("%d\n",pQ->data[pQ->front]);
}
int main(void)
{
	QUEUE Q;
	int choose,point;
	init_queue(&Q);

	while(1)
	{
		printf("(0)结束\t(1)入队\t(2)出队\n");
		scanf("%d",&choose);
	
		switch(choose){
			case 0:
				exit(EXIT_SUCCESS);
				break;
			case 1:
				input_queue(&Q);
				break;
			case 2:
				output_queue(&Q);
				break;
			default:
				printf("输入错误！\n");
				break;
		}
	}
	return 0;
}


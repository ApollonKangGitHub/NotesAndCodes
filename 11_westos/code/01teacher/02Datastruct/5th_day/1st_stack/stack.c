#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 *   init_stack
 *   in_stack
 *   out_stack
 *   full_stack
 *   empty_stack
 * */


#define	SIZE	16	

struct stack{
	int sta[SIZE];
	int top;
};

void init_stack(struct stack * s)
{
	memset(s->sta, 0, sizeof(s->sta));
	s->top = -1;
}
int if_full(struct stack* s)
{
	if(s->top == SIZE-1){
		printf("stack is full. \n");
		return -1;
	}
	else 
		return 0;
}
int in_stack(struct stack* s, int data)
{
	if(!(if_full(s))){
		(s->top)++;
		s->sta[s->top] = data;
		return 0;
	}
	else 
		return -1;
}
int if_empty(struct stack* s)
{
	if(s->top == -1){
		printf("stack if empty. \n");
		return -1;
	}
	else 
		return 0;
}
int out_stack(struct stack * s)
{
	if(!(if_empty(s))){
		int tmp = s->sta[s->top];
		(s->top)--;
		return tmp;
	}
	else 
		return 0;
}
int d_to_b(int data, struct stack *s)
{
	while(data){
		in_stack(s, data%2);
//		data = data / 2;
		data /= 2;
	}
	while(!(if_empty(s))){
		printf("%d ", out_stack(s));
	}
}
int main()
{
	struct stack S;
	init_stack(&S);
	int data = 38;

	d_to_b(data, &S);	
#if 0	
	in_stack(&S, 10);
	//in_stack(&S, 30);
	//in_stack(&S, 20);
	//in_stack(&S, 1);
	int ret = in_stack(&S, 13);
	if(ret < 0){
		exit(1);
	}
	ret = out_stack(&S);
	ret = out_stack(&S);
	printf("ret: %d\n", ret);
	ret = out_stack(&S);
	if(ret == 0){
		exit(1);
	}
	printf("ret: %d\n", ret);
#endif
	return 0;
}









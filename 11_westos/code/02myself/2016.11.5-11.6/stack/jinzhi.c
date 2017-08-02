# include<stdio.h>
# include<string.h>
# include<stdlib.h>

# define SIZE 32

typedef struct Stack{
	int sta_arr[SIZE];
	int top;
}STACK;

void init_stack(STACK *);

void init_stack(STACK * pS)
{
	memset(pS->sta_arr, 0, sizeof(pS->sta_arr));
	pS->top = -1;
}

int is_full(STACK * pS)
{
	return ((pS->top == SIZE-1) ? 0 : 1);
}
int is_empty(STACK * pS)
{
	return ((pS->top == -1) ? 0 : 1);
}

void input_stack(STACK * pS, int value)
{
	if(is_full(pS)){
		pS->top++;
		pS->sta_arr[pS->top] = value;
	}
}
void output_stack(STACK * pS)
{
	if(is_empty(pS))
		printf("%d",(pS->sta_arr)[pS->top]);
}

void invert(STACK * pS, int value, int type)
{
	int tmp,num = value;
	init_stack(pS);
	while(num){
		tmp = num % type;
		input_stack(pS,tmp);
		num = num / type;
	}
	while(pS->top != -1){
		output_stack(pS);
		pS->top--;
	}
	printf("\n");

}
int main (void)
{
	STACK S;
	int value, type;
	init_stack(&S);
	printf("请输入你要转换的十进制数字：\n");
	scanf("%d",&value);
	printf("请选择你要转换成的进制格式（2~9,如：2代表二进制）：\n");
	scanf("%d",&type);
	if(type > 9 || type < 2){
		printf("选择的进制格式暂时无法处理！\n");
		exit(EXIT_FAILURE);
	}
	invert(&S,value,type);
	return 0;
}

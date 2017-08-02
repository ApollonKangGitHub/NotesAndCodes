#include <stdio.h>
#include <string.h>

#define STACK_SIZE 1024
#define true 1
#define false 0
typedef short BOOL;

struct Stack{
    char space[STACK_SIZE];
    int top;
};

void init(struct Stack *s)
{
    s->top = 0;
    memset(s->space, 0, STACK_SIZE   );
}
BOOL isEmpty(struct Stack *s){
    return (s->top==0);
}
BOOL isFill(struct Stack *s){
    return (s->top==STACK_SIZE);//当前指针为栈顶元素的上面的地址
}
char pop(struct Stack *s){
    return (s->space[--s->top]);//先挪指针再出栈
}
void push(struct Stack *s, char c){
    s->space[s->top++] = c;//先压栈在挪指针
}
int main(void)
{
    struct Stack st;
    init(&st);
    if(!isFill(&st))
        push(&st,'a');
    if(!isFill(&st))
        push(&st,'b');
    if(!isFill(&st))
        push(&st,'c');
    if(!isFill(&st))
        push(&st,'d');
    if(!isFill(&st))
        push(&st,'e');
    if(!isFill(&st))
        push(&st,'f');

    st.top = 0;//可以随意修改，不安全性

    while(!isEmpty(&st))
        printf("%c\n",pop(&st));

    return 0;
}


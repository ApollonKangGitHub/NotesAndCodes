// c3-1.h 栈的顺序存储结构。在严书第46页
#define STACK_INIT_SIZE 10 
#define STACK_INCREMENT 2 
struct SqStack 
{ SElemType *base; 
  SElemType *top; 
  int stacksize; 
};


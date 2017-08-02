// c3-3.h 队列的顺序存储结构（循环队列）。在严书第64页
#define MAX_QSIZE 5 
struct SqQueue
{ QElemType *base; 
  int front; 
  int rear; 
};


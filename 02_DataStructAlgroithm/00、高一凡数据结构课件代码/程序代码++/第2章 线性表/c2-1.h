// c2-1.h 线性表的动态分配顺序存储结构。在严书第22页
#define LIST_INIT_SIZE 10 
#define LIST_INCREMENT 2 
struct SqList
{ ElemType *elem; 
  int length; 
  int listsize; 
};


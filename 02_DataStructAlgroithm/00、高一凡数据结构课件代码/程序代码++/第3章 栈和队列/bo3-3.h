// bo3-3.h 用单链表的基本操作实现链队列（存储结构由c3-2.h定义）的基本操作（9个）
typedef QElemType ElemType; 
#define LinkList QueuePtr 
#define LNode QNode
#include"bo2-2.h" 
void InitQueue(LinkQueue &Q)
{ 
  InitList(Q.front); 
  Q.rear=Q.front; 
}
void DestroyQueue(LinkQueue &Q)
{ 
  DestroyList(Q.front); 
  Q.rear=Q.front; 
}
void ClearQueue(LinkQueue &Q)
{ 
  ClearList(Q.front); 
  Q.rear=Q.front; 
}
Status QueueEmpty(LinkQueue Q)
{ 
  return ListEmpty(Q.front); 
}
int QueueLength(LinkQueue Q)
{ 
  return ListLength(Q.front); 
}
Status GetHead(LinkQueue Q, QElemType &e)
{ 
  return GetElem(Q.front, 1, e); 
}
void EnQueue(LinkQueue &Q, QElemType e)
{ 
  ListInsert(Q.front, ListLength(Q.front)+1, e); 
}
Status DeQueue(LinkQueue &Q, QElemType &e)
{ 
  if(Q.front->next==Q.rear) 
    Q.rear=Q.front; 
  return ListDelete(Q.front, 1, e); 
}
void QueueTraverse(LinkQueue Q, void(*visit)(QElemType))
{ 
  ListTraverse(Q.front, visit); 
}


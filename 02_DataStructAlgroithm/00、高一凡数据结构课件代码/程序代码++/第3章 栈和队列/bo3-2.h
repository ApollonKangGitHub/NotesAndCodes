// bo3-2.h 链队列（存储结构由c3-2.h定义）的基本操作（9个）
void InitQueue(LinkQueue &Q)
{ 
  Q.front=Q.rear=(QueuePtr)malloc(sizeof(QNode)); 
  if(!Q.front) 
    exit(OVERFLOW);
  Q.front->next=NULL; 
}
void DestroyQueue(LinkQueue &Q)
{ 
  while(Q.front) 
  { Q.rear=Q.front->next; 
    free(Q.front); 
    Q.front=Q.rear; 
  }
}
void ClearQueue(LinkQueue &Q)
{ 
  DestroyQueue(Q); 
  InitQueue(Q); 
}
Status QueueEmpty(LinkQueue Q)
{ 
  if(Q.front->next==NULL)
    return TRUE;
  else
    return FALSE;
}
int QueueLength(LinkQueue Q)
{ 
  int i=0; 
  QueuePtr p=Q.front; 
  while(Q.rear!=p) 
  { i++; 
    p=p->next; 
  }
  return i;
}
Status GetHead(LinkQueue Q, QElemType &e)
{ 
  QueuePtr p;
  if(Q.front==Q.rear) 
    return ERROR;
  p=Q.front->next; 
  e=p->data; 
  return OK;
}
void EnQueue(LinkQueue &Q, QElemType e)
{ 
  QueuePtr p=(QueuePtr)malloc(sizeof(QNode)); 
  if(!p)
    exit(OVERFLOW); 
  p->data=e; 
  p->next=NULL; 
  Q.rear->next=p; 
  Q.rear=p; 
}
Status DeQueue(LinkQueue &Q, QElemType &e)
{ 
  
  QueuePtr p;
  if(Q.front==Q.rear) 
    return ERROR;
  p=Q.front->next; 
  e=p->data; 
  Q.front->next=p->next; 
  if(Q.rear==p) 
    Q.rear=Q.front; 
  free(p); 
  return OK;
}
void QueueTraverse(LinkQueue Q, void(*visit)(QElemType))
{ 
  QueuePtr p=Q.front->next; 
  while(p) 
  { visit(p->data); 
    p=p->next; 
  }
  printf("\n");
}


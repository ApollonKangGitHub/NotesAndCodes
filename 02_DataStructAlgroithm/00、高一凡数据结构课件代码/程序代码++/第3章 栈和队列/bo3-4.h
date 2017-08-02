// bo3-4.h 循环队列（存储结构由c3-3.h定义）的基本操作（9个）
void InitQueue(SqQueue &Q)
{ 
  Q.base=(QElemType*)malloc(MAX_QSIZE*sizeof(QElemType));
  if(!Q.base) 
    exit(OVERFLOW);
  Q.front=Q.rear=0;
}
void DestroyQueue(SqQueue &Q)
{ 
  if(Q.base) 
    free(Q.base); 
  Q.base=NULL; 
  Q.front=Q.rear=0;
}
void ClearQueue(SqQueue &Q)
{ 
  Q.front=Q.rear=0;
}
Status QueueEmpty(SqQueue Q)
{ 
  if(Q.front==Q.rear) 
    return TRUE;
  else
    return FALSE;
}
int QueueLength(SqQueue Q)
{ 
  return(Q.rear-Q.front+MAX_QSIZE)%MAX_QSIZE;
}
Status GetHead(SqQueue Q, QElemType &e)
{ 
  if(Q.front==Q.rear) 
    return ERROR;
  e=Q.base[Q.front]; 
  return OK;
}
Status EnQueue(SqQueue &Q, QElemType e)
{ 
  if((Q.rear+1)%MAX_QSIZE==Q.front) 
    return ERROR;
  Q.base[Q.rear]=e; 
  Q.rear=(Q.rear+1)%MAX_QSIZE; 
  return OK;
}
Status DeQueue(SqQueue &Q, QElemType &e) 
{ 
  if(Q.front==Q.rear) 
    return ERROR;
  e=Q.base[Q.front]; 
  Q.front=(Q.front+1)%MAX_QSIZE; 
  return OK;
}
void QueueTraverse(SqQueue Q, void(*visit)(QElemType))
{ 
  int i=Q.front; 
  while(i!=Q.rear) 
  { visit(Q.base[i]); 
    i=(i+1)%MAX_QSIZE; 
  }
  printf("\n");
}


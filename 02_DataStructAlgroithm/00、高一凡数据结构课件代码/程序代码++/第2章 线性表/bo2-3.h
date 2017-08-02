// bo2-3.h 不设头结点的单链表（存储结构由c2-2.h定义）的部分基本操作（9个）
#define DestroyList ClearList 
void InitList(LinkList &L)
{ 
  L=NULL; 
}
void ClearList(LinkList &L)
{ 
  LinkList p;
  while(L) 
  { p=L; 
    L=L->next; 
    free(p); 
  }
}
Status ListEmpty(LinkList L)
{ 
  if(L)
    return FALSE;
  else
    return TRUE;
}
int ListLength(LinkList L)
{ 
  int i=0; 
  LinkList p=L; 
  while(p) 
  { i++; 
    p=p->next; 
  }
  return i;
}
Status GetElem(LinkList L, int i, ElemType &e)
{ 
  int j=1; 
  LinkList p=L; 
  if(i<1) 
    return ERROR;
  while(j<i && p) 
  { j++; 
    p=p->next; 
  }
  if(j==i && p) 
  { e=p->data; 
    return OK; 
  }
  return ERROR; 
}
int LocateElem(LinkList L, ElemType e, Status(*compare)(ElemType, ElemType))
{ 
  
  
  int i=0; 
  LinkList p=L; 
  while(p) 
  { i++; 
    if(compare(p->data, e)) 
      return i; 
    p=p->next; 
  }
  return 0; 
}
Status ListInsert(LinkList &L, int i, ElemType e)
{ 
  int j=1; 
  LinkList s, p=L; 
  if(i<1) 
    return ERROR;
  s=(LinkList)malloc(sizeof(LNode));
  
  s->data=e; 
  if(i==1) 
  { s->next=L; 
    L=s; 
  }
  else
  { 
    while(p && j<i-1) 
    { j++; 
      p=p->next; 
    }
    if(!p) 
      return ERROR; 
    s->next=p->next; 
    p->next=s; 
  }
  return OK; 
}
Status ListDelete(LinkList &L, int i, ElemType &e)
{ 
  int j=1; 
  LinkList q, p=L; 
  if(!L) 
    return ERROR; 
  else if(i==1) 
  { L=p->next; 
    e=p->data; 
    free(p); 
  }
  else
  { while(p->next && j<i-1) 
    { j++; 
      p=p->next; 
    }
    if(!p->next || j>i-1) 
      return ERROR; 
    q=p->next; 
    p->next=q->next; 
    e=q->data; 
    free(q); 
  }
  return OK; 
}
void ListTraverse(LinkList L, void(*vi)(ElemType))
{ 
  LinkList p=L; 
  while(p) 
  { vi(p->data); 
    p=p->next; 
  }
  printf("\n");
}


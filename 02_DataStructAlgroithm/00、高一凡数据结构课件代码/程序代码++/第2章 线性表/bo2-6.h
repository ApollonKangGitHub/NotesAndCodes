// bo2-6.h 设立尾指针的单循环链表（存储结构由c2-2.h定义）的12个基本操作
void InitList(LinkList &L)
{ 
  L=(LinkList)malloc(sizeof(LNode)); 
  if(!L) 
    exit(OVERFLOW);
  L->next=L; 
}
void ClearList(LinkList &L) 
{ 
  LinkList p, q;
  L=L->next; 
  p=L->next; 
  while(p!=L) 
  { q=p->next; 
    free(p); 
    p=q; 
  }
  L->next=L; 
}
void DestroyList(LinkList &L)
{ 
  ClearList(L); 
  free(L); 
  L=NULL; 
}
Status ListEmpty(LinkList L)
{ 
  if(L->next==L) 
    return TRUE;
  else
    return FALSE;
}
int ListLength(LinkList L)
{ 
  int i=0;
  LinkList p=L->next; 
  while(p!=L) 
  { i++; 
    p=p->next; 
  }
  return i;
}
Status GetElem(LinkList L, int i, ElemType &e)
{ 
  int j=1; 
  LinkList p=L->next->next; 
  if(i<=0 || i>ListLength(L)) 
    return ERROR;
  while(j<i) 
  { j++; 
    p=p->next; 
  }
  e=p->data; 
  return OK;
}
int LocateElem(LinkList L, ElemType e, Status(*compare)(ElemType,ElemType))
{ 
  
  
  int i=0; 
  LinkList p=L->next->next; 
  while(p!=L->next) 
  { i++; 
    if(compare(p->data, e)) 
      return i; 
    p=p->next; 
  }
  return 0; 
}
Status PriorElem(LinkList L, ElemType cur_e, ElemType &pre_e)
{ 
  
  
  LinkList q, p=L->next->next; 
  q=p->next; 
  while(q!=L->next) 
  { if(q->data==cur_e) 
    { pre_e=p->data; 
      return OK; 
    }
    p=q; 
    q=q->next; 
  }
  return ERROR; 
}
Status NextElem(LinkList L, ElemType cur_e, ElemType &next_e)
{ 
  
  
  LinkList p=L->next->next; 
  while(p!=L) 
  { if(p->data==cur_e) 
    { next_e=p->next->data; 
      return OK; 
    }
    p=p->next; 
  }
  return ERROR; 
}
Status ListInsert(LinkList &L, int i, ElemType e)
{ 
  LinkList p=L->next, s; 
  int j=0; 
  if(i<=0 || i>ListLength(L)+1) 
    return ERROR; 
  while(j<i-1) 
  { j++; 
    p=p->next; 
  }
  s=(LinkList)malloc(sizeof(LNode)); 
  s->data=e; 
  s->next=p->next; 
  p->next=s; 
  if(p==L) 
    L=s; 
  return OK; 
}
Status ListDelete(LinkList &L, int i, ElemType &e)
{ 
  LinkList q, p=L->next; 
  int j=0; 
  if(i<=0 || i>ListLength(L)) 
    return ERROR; 
  while(j<i-1) 
  { j++; 
    p=p->next; 
  }
  q=p->next; 
  p->next=q->next; 
  e=q->data; 
  if(L==q) 
    L=p; 
  free(q); 
  return OK; 
}
void ListTraverse(LinkList L, void(*vi)(ElemType))
{ 
  LinkList p=L->next->next; 
  while(p!=L->next) 
  { vi(p->data); 
    p=p->next; 
  }
  printf("\n");
}


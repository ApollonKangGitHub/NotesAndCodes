//OrderList.h 有序链表的基本操作（部分）
Status InitList(LinkList &L)
{ 
  LNode *p;
  p=(LNode*)malloc(sizeof(LNode)); 
  if(p)
  { p->next=NULL;
    L.head=L.tail=p;
    L.len=0;
    return OK;
  }
  else
    return ERROR;
}
Status DelFirst(LinkList &L, LNode *h, LNode* &q) 
{ 
  
  q=h->next;
  if(q) 
  { h->next=q->next;
    if(!h->next) 
      L.tail=h; 
    L.len--;
    return OK;
  }
  else
    return FALSE; 
}
ElemType GetCurElem(LNode *p)
{ 
  return p->data;
}
Status ListEmpty(LinkList L)
{ 
  if(L.len)
    return FALSE;
  else
    return TRUE;
}
Status OrderInsert(LinkList &L, ElemType e, int (*comp)(ElemType, ElemType))
{ 
  LNode *o, *p, *q;
  q=L.head;
  p=q->next;
  while(p!=NULL && comp(p->data, e)<0) 
  { q=p;
    p=p->next;
  }
  o=(LNode *)malloc(sizeof(LNode)); 
  o->data=e; 
  q->next=o; 
  o->next=p;
  L.len++; 
  if(!p) 
    L.tail=o; 
  return OK;
}


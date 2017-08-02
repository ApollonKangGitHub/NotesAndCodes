// func2-4.h 不设头结点的单链表（存储结构由c2-2.h定义）的扩展操作（1个），bo7-2.h用到
LinkList Point(LinkList L, ElemType e, Status(*equal)(ElemType, ElemType), LinkList &p)
{ 
  
  int j, i=LocateElem(L, e, equal); 
  if(i) 
  { if(i==1) 
    { p=NULL;
      return L;
    }
    p=L; 
    for(j=2; j<i; j++) 

      p=p->next;
    return p->next; 
  }
  return NULL; 
}


// bo2-5.h 静态链表（数据结构由c2-3.h定义）的基本操作（13个），包括算法2.13～2.16
#define DestroyList ClearList 
int Malloc(SLinkList space) 
{ 
  int i=space[0].cur; 
  if(i) 
    space[0].cur=space[i].cur; 
  return i; 
}
void Free(SLinkList space, int k) 
{ 
  space[k].cur=space[0].cur; 
  space[0].cur=k; 
}
void InitList(SLinkList L)
{ 
  
  int i;
  L[MAX_SIZE-1].cur=0; 
  for(i=0; i<MAX_SIZE-2; i++) 
    L[i].cur=i+1;
  L[MAX_SIZE-2].cur=0;
}
void ClearList(SLinkList L)
{ 
  int j, i=L[0].cur; 
  while(i) 
  { j=i; 
    i=L[i].cur; 
  }
  L[j].cur=L[MAX_SIZE-1].cur; 
  L[MAX_SIZE-1].cur=0; 
}
Status ListEmpty(SLinkList L)
{ 
  if(L[MAX_SIZE-1].cur==0) 
    return TRUE;
  else
    return FALSE;
}
int ListLength(SLinkList L)
{ 
  int j=0, i=L[MAX_SIZE-1].cur; 
  while(i) 
  { i=L[i].cur; 
    j++; 
  }
  return j;
}
Status GetElem(SLinkList L, int i, ElemType &e)
{ 
  int m, k=MAX_SIZE-1; 
  if(i<1 || i>ListLength(L)) 
    return ERROR;
  for(m=1; m<=i; m++) 
    k=L[k].cur; 
  e=L[k].data; 
  return OK;
}
int LocateElem(SLinkList L, ElemType e) 
{ 
  
  int i=L[MAX_SIZE-1].cur; 
  while(i && L[i].data!=e) 
    i=L[i].cur; 
  return i;
}
Status PriorElem(SLinkList L, ElemType cur_e, ElemType &pre_e)
{ 
  
  
  int j, i=L[MAX_SIZE-1].cur; 
  do 
  { j=i; 
    i=L[i].cur; 
  }while(i && cur_e!=L[i].data); 
  if(i) 
  { pre_e=L[j].data; 
    return OK;
  }
  return ERROR; 
}
Status NextElem(SLinkList L, ElemType cur_e, ElemType &next_e)
{ 
  
  
  int j, i=LocateElem(L, cur_e); 
  if(i) 
  { j=L[i].cur; 
    if(j) 
    { next_e=L[j].data; 
      return OK; 
    }
  }
  return ERROR; 
}
Status ListInsert(SLinkList L, int i, ElemType e)
{ 
  int m, j, k=MAX_SIZE-1; 
  if(i<1 || i>ListLength(L)+1) 
    return ERROR;
  j=Malloc(L); 
  if(j) 
  { L[j].data=e; 
    for(m=1; m<i; m++) 
      k=L[k].cur; 
    L[j].cur=L[k].cur; 
    L[k].cur=j; 
    return OK;
  }
  return ERROR;
}
Status ListDelete(SLinkList L, int i, ElemType &e)
{ 
  int j, k=MAX_SIZE-1; 
  if(i<1 || i>ListLength(L)) 
    return ERROR;
  for(j=1; j<i; j++) 
    k=L[k].cur; 
  j=L[k].cur; 
  L[k].cur=L[j].cur; 
  e=L[j].data; 
  Free(L, j); 
  return OK;
}
void ListTraverse(SLinkList L, void(*visit)(ElemType))
{ 
  int i=L[MAX_SIZE-1].cur; 
  while(i) 
  { visit(L[i].data); 
    i=L[i].cur; 
  }
  printf("\n");
}


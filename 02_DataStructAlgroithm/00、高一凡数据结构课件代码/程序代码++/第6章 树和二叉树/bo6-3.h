// bo6-3.h 树的二叉链表（孩子—兄弟）存储（存储结构由c6-2.h定义）的基本操作（16个）
#define ClearTree DestroyTree 
void InitTree(CSTree &T)
{ 
  T=NULL;
}
void DestroyTree(CSTree &T)
{ 
  if(T) 
  { DestroyTree(T->firstchild); 
    DestroyTree(T->nextsibling); 
    free(T); 
    T=NULL; 
  }
}
typedef CSTree QElemType; 
#include"c3-2.h" 
#include"bo3-2.h" 
void CreateTree(CSTree &T)
{ 
  char c[20]; 
  CSTree p, p1;
  LinkQueue q;
  int i, m;
  InitQueue(q); 
  printf("请输入根结点（字符型，#为空）：");
  scanf("%c%*c", &c[0]); 
  if(c[0]!=Nil) 
  { T=(CSTree)malloc(sizeof(CSNode)); 
    T->data=c[0]; 
    T->nextsibling=NULL; 
    EnQueue(q, T); 
    while(!QueueEmpty(q)) 
    { DeQueue(q, p); 
      printf("请按长幼顺序输入结点%c的所有孩子：", p->data);
      gets(c); 
      m=strlen(c);
      if(m>0) 
      { p1=p->firstchild=(CSTree)malloc(sizeof(CSNode)); 
        p1->data=c[0]; 
        EnQueue(q, p1); 
        for(i=1; i<m; i++) 
        { p1->nextsibling=(CSTree)malloc(sizeof(CSNode)); 
          p1=p1->nextsibling; 
          p1->data=c[i]; 
          EnQueue(q, p1); 
        }
        p1->nextsibling=NULL; 
      }
      else 
        p->firstchild=NULL; 
    }
  }
  else
    T=NULL; 
}
Status TreeEmpty(CSTree T)
{ 
  if(T) 
    return FALSE;
  else
    return TRUE;
}
int TreeDepth(CSTree T)
{ 
  CSTree p;
  int depth, max=0;
  if(!T) 
    return 0;
  for(p=T->firstchild; p; p=p->nextsibling)
  { 
    depth=TreeDepth(p); 
    if(depth>max) 
      max=depth;
  }
  return max+1; 
}
TElemType Value(CSTree p)
{ 
  return p->data;
}
TElemType Root(CSTree T)
{ 
  if(T)
    return Value(T);
  else
    return Nil;
}
CSTree Point(CSTree T, TElemType s)
{ 
  LinkQueue q;
  QElemType a;
  if(T) 
  { InitQueue(q); 
    EnQueue(q, T); 
    while(!QueueEmpty(q)) 
    { DeQueue(q, a); 
      if(a->data==s) 
        return a; 
      if(a->firstchild) 
        EnQueue(q, a->firstchild); 
      if(a->nextsibling) 
        EnQueue(q, a->nextsibling); 
    }
  }
  return NULL;
}
Status Assign(CSTree &T, TElemType cur_e, TElemType value)
{ 
  CSTree p;
  if(T) 
  { p=Point(T, cur_e); 
    if(p) 
    { p->data=value; 
      return OK;
    }
  }
  return ERROR; 
}
TElemType Parent(CSTree T, TElemType cur_e)
{ 
  
  CSTree p, t;
  LinkQueue q;
  InitQueue(q); 
  if(T) 
  { if(Value(T)==cur_e) 
       return Nil;
    EnQueue(q, T); 
    while(!QueueEmpty(q)) 
    { DeQueue(q, p); 
      if(p->firstchild) 
      { if(p->firstchild->data==cur_e) 
          return Value(p); 
        t=p; 
        p=p->firstchild; 
        EnQueue(q, p); 
        while(p->nextsibling) 
        { p=p->nextsibling; 
          if(Value(p)==cur_e) 
            return Value(t); 
          EnQueue(q, p); 
        }
      }
    }
  }
  return Nil; 
}
TElemType LeftChild(CSTree T, TElemType cur_e)
{ 
  
  CSTree f;
  f=Point(T, cur_e); 
  if(f && f->firstchild) 
    return f->firstchild->data; 
  else
    return Nil; 
}
TElemType RightSibling(CSTree T, TElemType cur_e)
{ 
  
  CSTree f;
  f=Point(T, cur_e); 
  if(f && f->nextsibling) 
    return f->nextsibling->data; 
  else
    return Nil; 
}
Status InsertChild(CSTree &T, CSTree p, int i, CSTree c)
{ 
  
  int j;
  CSTree q;
  if(T) 
  { if(i==1) 
    { c->nextsibling=p->firstchild; 
      p->firstchild=c; 
    }
    else 
    { q=p->firstchild; 
      j=2;
      while(q && j<i) 
      { q=q->nextsibling; 
        j++; 
      }
      if(j==i) 
      { c->nextsibling=q->nextsibling; 
        q->nextsibling=c; 
      }
      else 
        return ERROR;
    }
    return OK;
  }
  else 
    return ERROR;
}
Status DeleteChild(CSTree &T, CSTree p, int i)
{ 
  
  CSTree b, q;
  int j;
  if(T) 
  { if(i==1) 
    { 
      b=p->firstchild; 
      p->firstchild=b->nextsibling; 
      b->nextsibling=NULL; 
      DestroyTree(b); 
    }
    else 
    { q=p->firstchild; 
      j=2;
      while(q && j<i) 
      { q=q->nextsibling; 
        j++; 
      }
      if(j==i) 
      { b=q->nextsibling; 
        q->nextsibling=b->nextsibling; 
        b->nextsibling=NULL; 
        DestroyTree(b); 
      }
      else 
        return ERROR;
    }
    return OK;
  }
  else
    return ERROR;
}
void PostOrderTraverse(CSTree T, void(*Visit)(TElemType))
{ 
  CSTree p;
  if(T)
  { if(T->firstchild) 
    { PostOrderTraverse(T->firstchild, Visit); 
      p=T->firstchild->nextsibling; 
      while(p) 
      { PostOrderTraverse(p, Visit); 
        p=p->nextsibling; 
      }
    }
    Visit(Value(T)); 
  }
}
void LevelOrderTraverse(CSTree T, void(*Visit)(TElemType))
{ 
  CSTree p;
  LinkQueue q;
  InitQueue(q); 
  if(T) 
  { Visit(Value(T)); 
    EnQueue(q, T); 
    while(!QueueEmpty(q)) 
    { DeQueue(q, p); 
      if(p->firstchild) 
      { p=p->firstchild; 
        Visit(Value(p)); 
        EnQueue(q, p); 
        while(p->nextsibling) 
        { p=p->nextsibling; 
          Visit(Value(p)); 
          EnQueue(q, p); 
        }
      }
    }
  }
  printf("\n");
}


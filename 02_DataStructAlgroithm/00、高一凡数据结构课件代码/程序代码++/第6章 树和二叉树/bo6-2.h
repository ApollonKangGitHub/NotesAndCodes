// bo6-2.h 二叉链表（存储结构由c6-1.h定义）的基本操作（18个），包括算法6.2～6.4
Status BiTreeEmpty(BiTree T)
{ 
  if(T)
    return FALSE;
  else
    return TRUE;
}
int BiTreeDepth(BiTree T)
{ 
  int i, j;
  if(!T)
    return 0; 
  i=BiTreeDepth(T->lchild); 
  j=BiTreeDepth(T->rchild); 
  return i>j ? i+1 : j+1; 
}
TElemType Root(BiTree T)
{ 
  if(BiTreeEmpty(T)) 
    return Nil; 
  else 
    return T->data; 
}
TElemType Value(BiTree p)
{ 
  return p->data;
}
void Assign(BiTree p, TElemType value)
{ 
  p->data=value;
}
typedef BiTree QElemType; 
#include"c3-2.h" 
#include"bo3-2.h" 
BiTree Point(BiTree T, TElemType s)
{ 
  LinkQueue q;
  QElemType a;
  if(T) 
  { InitQueue(q); 
    EnQueue(q, T); 
    while(!QueueEmpty(q)) 
    { DeQueue(q, a); 
      if(a->data==s) 
      { DestroyQueue(q); 
        return a; 
      }
      if(a->lchild) 
        EnQueue(q, a->lchild); 
      if(a->rchild) 
        EnQueue(q, a->rchild); 
    }
    DestroyQueue(q); 
  }
  return NULL; 
}
TElemType LeftChild(BiTree T, TElemType e)
{ 
  
  BiTree a;
  if(T) 
  { a=Point(T, e); 
    if(a && a->lchild) 
      return a->lchild->data; 
  }
  return Nil; 
}
TElemType RightChild(BiTree T, TElemType e)
{ 
  
  BiTree a;
  if(T) 
  { a=Point(T, e); 
    if(a && a->rchild) 
      return a->rchild->data; 
  }
  return Nil; 
}
Status DeleteChild(BiTree p, int LR) 
{ 
  
  if(p) 
  { if(LR==0) 
      ClearBiTree(p->lchild); 
    else if(LR==1) 
      ClearBiTree(p->rchild); 
    return OK;
  }
  return ERROR; 
}
void PostOrderTraverse(BiTree T, void(*Visit)(TElemType))
{ 
  
  if(T) 
  { PostOrderTraverse(T->lchild, Visit); 
    PostOrderTraverse(T->rchild, Visit); 
    Visit(T->data); 
  }
}
void LevelOrderTraverse(BiTree T, void(*Visit)(TElemType))
{ 
  
  LinkQueue q;
  QElemType a;
  if(T) 
  { InitQueue(q); 
    EnQueue(q, T); 
    while(!QueueEmpty(q)) 
    { DeQueue(q, a); 
      Visit(a->data); 
      if(a->lchild!=NULL) 
        EnQueue(q, a->lchild); 
      if(a->rchild!=NULL) 
        EnQueue(q, a->rchild); 
    }
    printf("\n");
    DestroyQueue(q); 
  }
}
void CreateBiTree(BiTree &T)
{ 
  
  TElemType ch;
  scanf(form, &ch); 
  if(ch==Nil) 
    T=NULL;
  else 
  { T=(BiTree)malloc(sizeof(BiTNode)); 
    if(!T)
      exit(OVERFLOW);
    T->data=ch; 
    CreateBiTree(T->lchild); 
    CreateBiTree(T->rchild); 
  }
}
TElemType Parent(BiTree T, TElemType e)
{ 
  
  LinkQueue q;
  QElemType a;
  if(T) 
  { InitQueue(q); 
    EnQueue(q, T); 
    while(!QueueEmpty(q)) 
    { DeQueue(q, a); 
      if(a->lchild && a->lchild->data==e || a->rchild && a->rchild->data==e)
      
      { DestroyQueue(q); 
        return a->data; 
      }
      else 
      { if(a->lchild) 
          EnQueue(q, a->lchild); 
        if(a->rchild) 
          EnQueue(q, a->rchild); 
      }
    }
    DestroyQueue(q); 
  }
  return Nil; 
}
TElemType LeftSibling(BiTree T, TElemType e)
{ 
  
  TElemType a;
  BiTree p;
  if(T) 
  { a=Parent(T, e); 
    if(a!=Nil) 
    { p=Point(T, a); 
      if(p->lchild && p->rchild && p->rchild->data==e) 
        return p->lchild->data; 
    }
  }
  return Nil; 
}
TElemType RightSibling(BiTree T, TElemType e)
{ 
  
  TElemType a;
  BiTree p;
  if(T) 
  { a=Parent(T, e); 
    if(a!=Nil) 
    { p=Point(T, a); 
      if(p->lchild && p->rchild && p->lchild->data==e) 
        return p->rchild->data; 
    }
  }
  return Nil; 
}
Status InsertChild(BiTree p, int LR, BiTree c) 
{ 
  
  
  
  if(p) 
  { if(LR==0) 
    { c->rchild=p->lchild; 
      p->lchild=c; 
    }
    else 
    { c->rchild=p->rchild; 
      p->rchild=c; 
    }
    return OK;
  }
  return ERROR; 
}
typedef BiTree SElemType; 
#include"c3-1.h" 
#include"bo3-1.h" 
void InOrderTraverse1(BiTree T, void(*Visit)(TElemType))
{ 
  
  SqStack S;
  InitStack(S); 
  while(T!=NULL || !StackEmpty(S)) 
  { if(T!=NULL) 
    { 
      Push(S, T); 
      T=T->lchild; 
    }
    else 
    { Pop(S, T); 
      Visit(T->data); 
      T=T->rchild; 
    }
  }
  printf("\n");
  DestroyStack(S); 
}
void InOrderTraverse2(BiTree T, void(*Visit)(TElemType))
{ 
  
  SqStack S;
  BiTree p;
  InitStack(S); 
  Push(S, T); 
  while(!StackEmpty(S)) 
  { while(GetTop(S, p) && p) 
      Push(S, p->lchild); 
    Pop(S, p); 
    if(!StackEmpty(S)) 
    { Pop(S, p); 
      Visit(p->data); 
      Push(S, p->rchild); 
    }
  }
  printf("\n");
  DestroyStack(S); 
}


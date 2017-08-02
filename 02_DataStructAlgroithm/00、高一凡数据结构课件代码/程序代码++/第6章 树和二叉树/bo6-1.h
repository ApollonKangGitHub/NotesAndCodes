// bo6-1.h ���������4�����������������㷨6.1��func8-4.h�ȵ���
#define ClearBiTree DestroyBiTree 
void InitBiTree(BiTree &T)
{ 
  T=NULL;
}
void DestroyBiTree(BiTree &T)
{ 
  if(T) 
  { DestroyBiTree(T->lchild); 
    DestroyBiTree(T->rchild); 
    free(T); 
    T=NULL; 
  }
}
void PreOrderTraverse(BiTree T, void(*Visit)(TElemType))
{ 
  
  if(T) 
  { Visit(T->data); 
    PreOrderTraverse(T->lchild, Visit); 
    PreOrderTraverse(T->rchild, Visit); 
  }
}
void InOrderTraverse(BiTree T, void(*Visit)(TElemType))
{ 
  
  if(T)
  { InOrderTraverse(T->lchild, Visit); 
    Visit(T->data); 
    InOrderTraverse(T->rchild, Visit); 
  }
}


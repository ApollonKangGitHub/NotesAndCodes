// bo6-4.h main6-2.cpp��algo7-3.cpp����
void PreOrderTraverse(CSTree T, void(*Visit)(TElemType))
{ 
  if(T)
  { Visit(T->data); 
    PreOrderTraverse(T->firstchild, Visit); 
    PreOrderTraverse(T->nextsibling, Visit); 
  }
}


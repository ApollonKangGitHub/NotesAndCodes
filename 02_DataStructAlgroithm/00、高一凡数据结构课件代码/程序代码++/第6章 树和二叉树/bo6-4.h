// bo6-4.h main6-2.cppºÍalgo7-3.cppµ÷ÓÃ
void PreOrderTraverse(CSTree T, void(*Visit)(TElemType))
{ 
  if(T)
  { Visit(T->data); 
    PreOrderTraverse(T->firstchild, Visit); 
    PreOrderTraverse(T->nextsibling, Visit); 
  }
}


// func2-4.h ����ͷ���ĵ������洢�ṹ��c2-2.h���壩����չ������1������bo7-2.h�õ�
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


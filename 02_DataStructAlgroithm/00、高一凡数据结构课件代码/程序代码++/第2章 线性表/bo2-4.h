// bo2-4.h ����ͷ���ĵ������洢�ṹ��c2-2.h���壩�Ĳ��ֻ���������2����
Status PriorElem(LinkList L, ElemType cur_e, ElemType &pre_e)
{ 
  
  
  LinkList q, p=L; 
  while(p->next) 
  { q=p->next; 
    if(q->data==cur_e) 
    { pre_e=p->data; 
      return OK; 
    }
    p=q; 
  }
  return ERROR; 
}
Status NextElem(LinkList L, ElemType cur_e, ElemType &next_e)
{ 
  
  
  LinkList p=L; 
  while(p->next) 
  { if(p->data==cur_e) 
    { next_e=p->next->data; 
      return OK; 
    }
    p=p->next; 
  }
  return ERROR; 
}


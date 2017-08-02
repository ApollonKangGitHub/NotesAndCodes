// func2-1.h À„∑®2.1∫Õ2.2
void Union(List &La, List Lb) 
{ 
  ElemType e;
  int La_len, Lb_len;
  int i;
  La_len=ListLength(La); 
  Lb_len=ListLength(Lb); 
  for(i=1; i<=Lb_len; i++) 
  { GetElem(Lb, i, e); 
    if(!LocateElem(La, e, equal)) 
      ListInsert(La, ++La_len, e); 
  }
}
void MergeList(List La, List Lb, List &Lc) 
{ 
  
  int i=1, j=1, k=0;
  int La_len, Lb_len;
  ElemType ai, bj;
  InitList(Lc); 
 
  La_len=ListLength(La); 
  Lb_len=ListLength(Lb); 
  while(i<=La_len && j<=Lb_len) 
  { GetElem(La, i, ai); 
    GetElem(Lb, j, bj); 
    if(ai<=bj) 
    { ListInsert(Lc, ++k, ai); 
      i++; 
    }
    else
    { ListInsert(Lc, ++k, bj); 
      j++; 
    }
  } 
  while(i<=La_len) 
  { GetElem(La, i++, ai); 
    ListInsert(Lc, ++k, ai); 
  }
  while(j<=Lb_len) 
  { GetElem(Lb, j++, bj); 
    ListInsert(Lc, ++k, bj); 
  }
}


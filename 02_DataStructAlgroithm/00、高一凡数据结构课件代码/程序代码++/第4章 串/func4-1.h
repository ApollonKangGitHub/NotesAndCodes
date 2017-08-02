// func4-1.h 与存储结构无关的两个基本操作
int Index(String S, String T, int pos) 
{ 
  
  int n, m, i;
  String sub;
  InitString(sub); 
  if(pos>0)
  { n=StrLength(S); 
    m=StrLength(T); 
    i=pos;
    while(i<=n-m+1) 
    { SubString(sub, S, i, m); 
      if(StrCompare(sub, T)!=0) 
        i++; 
      else 
        return i; 
    }
  }
  return 0; 
}
Status Replace(String &S, String T, String V)
{ 
  
  int i=1; 
  Status k;
  if(StrEmpty(T)) 
    return ERROR;
  while(i)
  { i=Index(S, T, i); 
    if(i) 
    { StrDelete(S, i, StrLength(T)); 
      k=StrInsert(S, i, V); 
      if(!k) 
        return ERROR;
      i+=StrLength(V); 
    }
  };
  return OK;
}


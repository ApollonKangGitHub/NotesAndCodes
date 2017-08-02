// func6-2.h 程序algo6-1.cpp和algo6-2.cpp要调用的2个函数
#define Order 
int min(HuffmanTree t, int i)
{ 
  int j, m;
  unsigned int k=UINT_MAX; 
  for(j=1; j<=i; j++) 
    if(t[j].weight<k && t[j].parent==0) 
    { k=t[j].weight; 
      m=j; 
    }
  t[m].parent=1; 
  return m; 
}
void select(HuffmanTree t, int i, int &s1, int &s2)
{ 
#ifdef Order 
  int j;
#endif
  s1=min(t, i); 
  s2=min(t, i); 
#ifdef Order 
  if(s1>s2) 
  { 
    j=s1;
    s1=s2; 
    s2=j; 
  }
#endif
}


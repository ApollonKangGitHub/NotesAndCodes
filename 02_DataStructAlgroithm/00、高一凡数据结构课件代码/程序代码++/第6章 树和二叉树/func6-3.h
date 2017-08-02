// func6-3.h 算法6.12的前半部分
  int m, i, s1, s2;
  unsigned c;
  HuffmanTree p;
  char *cd;
  if(n<=1) 
    return;
  m=2*n-1; 
  HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode)); 
  for(p=HT+1, i=1; i<=n; i++, p++, w++) 
  { 
    (*p).weight=*w; 
    (*p).parent=0; 
    (*p).lchild=0; 
    (*p).rchild=0;
  }
  for(; i<=m; i++, p++) 
    (*p).parent=0; 
  for(i=n+1; i<=m; i++) 
  { 
    select(HT, i-1, s1, s2);
    HT[s1].parent=HT[s2].parent=i; 
    HT[i].lchild=s1; 
    HT[i].rchild=s2;
    HT[i].weight=HT[s1].weight+HT[s2].weight; 
  }


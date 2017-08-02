// bo5-2.h 三元组稀疏矩阵的基本操作（4个），包括算法5.1
Status CreateSMatrix(TSMatrix &M)
{ 
  int i;
  Triple T;
  Status k;
  printf("请输入矩阵的行数,列数,非零元素个数：");
  scanf("%d,%d,%d", &M.mu, &M.nu, &M.tu);
  if(M.tu>MAX_SIZE) 
    return ERROR;
  M.data[0].i=0; 
  for(i=1; i<=M.tu; i++) 
  { do
    { printf("请按行序顺序输入第%d个非零元素所在的行（1～%d）,列（1～%d）,元素值：", 
      i, M.mu, M.nu);
      scanf("%d,%d,%d", &T.i, &T.j, &T.e);
      k=0; 
      if(T.i<1 || T.i>M.mu || T.j<1 || T.j>M.nu) 
        k=1;
      if(T.i<M.data[i-1].i || T.i==M.data[i-1].i && T.j<=M.data[i-1].j)
        k=1; 
    }while(k); 
    M.data[i]=T; 
  }
  return OK;
}
Status AddSMatrix(TSMatrix M, TSMatrix N, TSMatrix &Q)
{ 
  int m=1, n=1, q=0;
  if(M.mu!=N.mu || M.nu!=N.nu) 
    return ERROR;
  Q.mu=M.mu; 
  Q.nu=M.nu;
  while(m<=M.tu && n<=N.tu) 
    switch(comp(M.data[m].i, N.data[n].i)) 
    { case -1: Q.data[++q]=M.data[m++]; 
               break;
      case  0: switch(comp(M.data[m].j, N.data[n].j))
               { 
                 case -1: Q.data[++q]=M.data[m++]; 
                          break;
                 case  0: 
                          Q.data[++q]=M.data[m++];
                          Q.data[q].e+=N.data[n++].e;
                          if(Q.data[q].e==0) 
                            q--;
                          break;
                 case  1: Q.data[++q]=N.data[n++]; 
               }
               break;
      case  1: Q.data[++q]=N.data[n++]; 
    } 
  while(m<=M.tu) 
    Q.data[++q]=M.data[m++];
  while(n<=N.tu) 
    Q.data[++q]=N.data[n++];
  if(q>MAX_SIZE) 
    return ERROR;
  Q.tu=q; 
  return OK;
}
void TransposeSMatrix(TSMatrix M, TSMatrix &T)
{ 
  int p, col, q=1; 
  T.mu=M.nu; 
  T.nu=M.mu; 
  T.tu=M.tu; 
  if(T.tu) 
    for(col=1; col<=M.nu; col++) 
      for(p=1; p<=M.tu; p++) 
        if(M.data[p].j==col) 
        { T.data[q].i=M.data[p].j; 
          T.data[q].j=M.data[p].i;
          T.data[q++].e=M.data[p].e; 
        }
}
Status MultSMatrix(TSMatrix M, TSMatrix N, TSMatrix &Q)
{ 
  int i, j, q, p;
  ElemType Qs; 
  TSMatrix T; 
  if(M.nu!=N.mu) 
    return ERROR;
  Q.mu=M.mu; 
  Q.nu=N.nu; 
  Q.tu=0; 
  TransposeSMatrix(N, T); 
  for(i=1; i<=Q.mu; i++) 
  { q=1; 
    for(j=1; j<=T.mu; j++) 
    { Qs=0; 
      p=1; 
      while(M.data[p].i<i) 
        p++;
      while(T.data[q].i<j) 
        q++;
      while(p<=M.tu && q<=T.tu && M.data[p].i==i && T.data[q].i==j)
      
        switch(comp(M.data[p].j, T.data[q].j))
        { 
          case -1: p++; 
                   break;
         
          case  0: Qs+=M.data[p++].e*T.data[q++].e;
                   break;
          case  1: q++; 
        }
      if(Qs) 
      { if(++Q.tu>MAX_SIZE) 
          return ERROR;
        Q.data[Q.tu].i=i; 
        Q.data[Q.tu].j=j;
        Q.data[Q.tu].e=Qs;
      }
    }
  }
  return OK;
}


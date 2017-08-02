// bo5-4.h 行逻辑链接稀疏矩阵（存储结构由c5-3.h定义）的基本操作（4个），包括算法5.3
Status CreateSMatrix(RLSMatrix &M)
{ 
  int i, j;
  Triple T;
  Status k;
  printf("请输入矩阵的行数,列数,非零元素个数：");
  scanf("%d,%d,%d", &M.mu, &M.nu, &M.tu);
  if(M.tu>MAX_SIZE || M.mu>MAX_RC) 
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
  for(i=1; i<=M.mu; i++) 
    M.rpos[i]=1;
  for(i=1; i<=M.tu; i++) 
    for(j=M.data[i].i+1; j<=M.mu; j++) 
      M.rpos[j]++; 
  return OK;
}
Status AddSMatrix(RLSMatrix M, RLSMatrix N, RLSMatrix &Q)
{ 
  int k, p, q, up, uq;
  if(M.mu!=N.mu || M.nu!=N.nu) 
    return ERROR;
  Q.mu=M.mu; 
  Q.nu=M.nu;
  Q.tu=0; 
  for(k=1; k<=M.mu; k++) 
  { Q.rpos[k]=Q.tu+1; 
    p=M.rpos[k]; 
    q=N.rpos[k]; 
    if(k<M.mu) 
    { up=M.rpos[k+1]; 
      uq=N.rpos[k+1];
    }
    else 
    { up=M.tu+1; 
      uq=N.tu+1;
    }
    while(p<up && q<uq) 
      switch(comp(M.data[p].j, N.data[q].j)) 
      { 
        case -1: Q.data[++Q.tu]=M.data[p++];
                 break;
        case  0: if(M.data[p].e+N.data[q].e!=0)
                 { 
                   Q.data[++Q.tu]=M.data[p]; 
                   Q.data[Q.tu].e+=N.data[q].e; 
                 }
                 p++; 
                 q++;
                 break;
        
        case  1: Q.data[++Q.tu]=N.data[q++];
      } 
    while(p<M.rpos[k+1] && p<=M.tu) 
      Q.data[++Q.tu]=M.data[p++]; 
    while(q<N.rpos[k+1] && q<=N.tu) 
      Q.data[++Q.tu]=N.data[q++]; 
  }
  if(Q.tu>MAX_SIZE) 
    return ERROR;
  else
    return OK;
}
void TransposeSMatrix(RLSMatrix M, RLSMatrix &T)
{ 
  int i, j, k, num[MAX_RC+1]; 
  T.mu=M.nu; 
  T.nu=M.mu; 
  T.tu=M.tu; 
  if(T.tu) 
  { for(i=1; i<=T.mu; i++) 
      num[i]=0; 
    for(i=1; i<=M.tu; i++) 
      num[M.data[i].j]++; 
    T.rpos[1]=1; 
    for(i=2; i<=T.mu; i++) 
      T.rpos[i]=T.rpos[i-1]+num[i-1]; 
    for(i=1; i<=T.mu; i++)
      num[i]=T.rpos[i]; 
    for(i=1; i<=M.tu; i++) 
    { j=M.data[i].j; 
      k=num[j]++; 
      T.data[k].i=M.data[i].j; 
      T.data[k].j=M.data[i].i;
      T.data[k].e=M.data[i].e;
    }
  }
}
Status MultSMatrix(RLSMatrix M, RLSMatrix N, RLSMatrix &Q)
{ 
  int arow, brow, p, q, ccol, ctemp[MAX_RC+1], t, tp;
  if(M.nu!=N.mu) 
    return ERROR;
  Q.mu=M.mu; 
  Q.nu=N.nu; 
  Q.tu=0; 
  if(M.tu*N.tu!=0) 
    for(arow=1; arow<=M.mu; arow++) 
    { for(ccol=1; ccol<=Q.nu; ccol++) 
        ctemp[ccol]=0; 
      Q.rpos[arow]=Q.tu+1; 
      if(arow<M.mu) 
        tp=M.rpos[arow+1]; 
      else 
        tp=M.tu+1; 
      for(p=M.rpos[arow]; p<tp; p++) 
      { brow=M.data[p].j; 
        if(brow<N.mu) 
          t=N.rpos[brow+1]; 
        else 
          t=N.tu+1; 
        for(q=N.rpos[brow]; q<t; q++) 
        { ccol=N.data[q].j; 
          ctemp[ccol]+=M.data[p].e*N.data[q].e; 
        }
      } 
      for(ccol=1; ccol<=Q.nu; ccol++) 
        if(ctemp[ccol]) 
        { if(++Q.tu>MAX_SIZE) 
            return ERROR;
          Q.data[Q.tu].i=arow; 
          Q.data[Q.tu].j=ccol;
          Q.data[Q.tu].e=ctemp[ccol];
        }
    }
  return OK;
}
Status MultSMatrix1(RLSMatrix M, RLSMatrix N, RLSMatrix &Q)
{ 
  int i, j, q, p, up, uq;
  ElemType Qs; 
  RLSMatrix T; 
  if(M.nu!=N.mu) 
    return ERROR;
  Q.mu=M.mu; 
  Q.nu=N.nu; 
  Q.tu=0; 
  TransposeSMatrix(N, T); 
  for(i=1; i<=Q.mu; i++) 
    for(j=1; j<=Q.nu; j++) 
    { Qs=0; 
      p=M.rpos[i]; 
      q=T.rpos[j]; 
      if(i<M.mu) 
        up=M.rpos[i+1]; 
      else 
        up=M.tu+1; 
      if(j<T.mu) 
        uq=T.rpos[j+1]; 
      else 
        uq=T.tu+1; 
      while(p<up && q<uq) 
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
  return OK;
}


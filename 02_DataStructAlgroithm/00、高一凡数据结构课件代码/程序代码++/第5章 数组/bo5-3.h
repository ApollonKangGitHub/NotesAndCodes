// bo5-3.h 三元组稀疏矩阵的基本操作（4个），也可用于行逻辑链接结构
void DestroySMatrix(TSMatrix &M)
{ 
  M.mu=M.nu=M.tu=0;
}
void PrintSMatrix(TSMatrix M)
{ 
  int i, j, k=1; 
  Triple *p=M.data+1; 
  for(i=1; i<=M.mu; i++) 
  { for(j=1; j<=M.nu; j++) 
      if(k<=M.tu && p->i==i && p->j==j)
      { printf("%3d", (p++)->e); 
        k++; 
      }
      else 
        printf("%3d", 0); 
    printf("\n");
  }
}
void CopySMatrix(TSMatrix M, TSMatrix &T)
{ 
  T=M;
}
Status SubtSMatrix(TSMatrix M, TSMatrix N, TSMatrix &Q)
{ 
  int i;
  if(M.mu!=N.mu || M.nu!=N.nu) 
    return ERROR;
  for(i=1; i<=N.tu; i++) 
    N.data[i].e*=-1;
  AddSMatrix(M, N, Q); 
  return OK;
}


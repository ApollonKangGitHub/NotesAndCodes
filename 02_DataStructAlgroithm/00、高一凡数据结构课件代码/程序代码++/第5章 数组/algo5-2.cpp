// algo5-2.cpp 实现算法5.2的程序
#include"c1.h"
typedef int ElemType; 
#include"c5-2.h" 
#include"func5-1.h" 
#include"bo5-2.h" 
#include"bo5-3.h" 
void FastTransposeSMatrix(TSMatrix M, TSMatrix &T)
{ 
  int p, q, col, *num, *cpot;
  num=(int*)malloc((M.nu+1)*sizeof(int)); 
  cpot=(int*)malloc((M.nu+1)*sizeof(int));
  T.mu=M.nu; 
  T.nu=M.mu; 
  T.tu=M.tu; 
  if(T.tu) 
  { for(col=1; col<=M.nu; col++) 
      num[col]=0; 
    for(p=1; p<=M.tu; p++) 
      ++num[M.data[p].j]; 
    cpot[1]=1; 
    for(col=2; col<=M.nu; col++) 
      cpot[col]=cpot[col-1]+num[col-1];
    for(p=1; p<=M.tu; p++) 
    { col=M.data[p].j; 
      q=cpot[col]; 
      T.data[q].i=M.data[p].j; 
      T.data[q].j=M.data[p].i;
      T.data[q].e=M.data[p].e;
      cpot[col]++; 
    }
  }
  free(num); 
  free(cpot);
}
void main()
{
  TSMatrix A, B;
  printf("创建矩阵A：");
  CreateSMatrix(A); 
  PrintSMatrix(A); 
  FastTransposeSMatrix(A, B); 
  printf("矩阵B（A的快速转置）：\n");
  PrintSMatrix(B); 
}


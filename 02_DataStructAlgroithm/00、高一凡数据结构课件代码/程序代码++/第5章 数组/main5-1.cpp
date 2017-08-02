// main5-1.cpp 检验bo5-1.h的主程序
#include"c1.h"
typedef int ElemType; 
#include"c5-1.h" 
#include"bo5-1.h" 
void main()
{
  Array A;
  int i, j, k, dim=3, bound1=3, bound2=4, bound3=2; 
  ElemType e;
  InitArray(A, dim, bound1, bound2, bound3); 
  printf("A.bounds=");
  for(i=0; i<dim; i++) 
    printf("%d ", *(A.bounds+i));
  printf("\nA.constants=");
  for(i=0; i<dim; i++) 
    printf("%d ", *(A.constants+i));
  printf("\n%d页%d行%d列矩阵元素如下：\n", bound1, bound2, bound3);
  for(i=0; i<bound1; i++)
  { for(j=0; j<bound2; j++)
    { for(k=0; k<bound3; k++)
      { Assign(A, i*100+j*10+k, i, j, k); 
        Value(e, A, i, j, k); 
        printf("A[%d][%d][%d]=%2d ", i, j, k, e); 
      }
      printf("\n");
    }
    printf("\n");
  }
  printf("A.base=\n");
  for(i=0; i<bound1*bound2*bound3; i++) 
  { printf("%4d", *(A.base+i));
    if(i%(bound2*bound3)==bound2*bound3-1)
      printf("\n");
  }
  printf("A.dim=%d\n", A.dim);
  DestroyArray(A);
}


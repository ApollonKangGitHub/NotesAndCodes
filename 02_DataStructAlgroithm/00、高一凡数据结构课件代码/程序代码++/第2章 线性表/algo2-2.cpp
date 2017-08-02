// algo2-2.cpp 用SqList类型和LinkList类型分别实现算法2.1和2.2的程序
#include"c1.h"
typedef int ElemType; 
#define Sq 
#ifdef Sq
  #include"c2-1.h" 
  #include"bo2-1.h" 
  typedef SqList List; 
  #define printer print1 
#else
  #include"c2-2.h" 
  #include"bo2-2.h" 
  typedef LinkList List; 
  #define printer print 
#endif
#include"func2-2.h" 
#include"func2-1.h" 
void main()
{
  List La, Lb, Lc;
  int j, b[7]={2, 6, 8, 9, 11, 15, 20};
  InitList(La); 
  for(j=1; j<=5; j++) 
    ListInsert(La, j, j);
  printf("La= ");
  ListTraverse(La, printer); 
  InitList(Lb); 
  for(j=1; j<=5; j++) 
    ListInsert(Lb, j, 2*j);
  printf("Lb= ");
  ListTraverse(Lb, printer); 
  Union(La, Lb); 
  printf("new La= ");
  ListTraverse(La, printer); 
  ClearList(Lb); 
  for(j=1; j<=7; j++) 
    ListInsert(Lb, j, b[j-1]);
  printf("Lb= ");
  ListTraverse(Lb, printer); 
  MergeList(La, Lb, Lc); 
  printf("Lc= ");
  ListTraverse(Lc, printer); 
}


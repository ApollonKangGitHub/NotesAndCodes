// algo8-6.cpp 检验bo8-4.h的程序
#include"c1.h"
#define m 3 
#define EMPTY 0 
#define N 12 
int s=(m+1)/2; 
typedef int KeyType; 
struct Others 
{ int order; 
};
#include"c8-2.h" 
#include"c8-4.h" 
#include"c8-5.h" 
#include"c8-6.h" 
Record R[N]; 
#include"bo8-4.h" 
#include"func8-6.h" 
void main()
{
  Record e;
  BTree t;
  Result u;
  KeyType j;
  int i, n;
  for(i=0; i<N; i++) 
    R[i].key=EMPTY;
  FILE *f; 
  InitDSTable(t); 
  f=fopen("f8-5.txt", "r"); 
  fscanf(f, "%d", &n); 
  for(i=0; i<n; i++) 
  { fscanf(f, "%d %d", &e.key, &e.others); 
    if(InsertRecord(t, e)==FALSE) 
      printf("插入(%d,%d)失败。\n", e.key, e.others.order);
  }
  fclose(f); 
  printf("按关键字的顺序遍历B_树t：\n");
  TraverseDSTable(t, Visit); 
  for(i=1; i<=4; i++) 
  { printf("\n请输入待查找记录的关键字：");
    InputKey(j); 
    u=SearchBTree(t, j); 
    if(u.tag) 
      Visit(*(u.pt), u.i); 
    else 
      printf("未找到");
    printf(" u.i=%d u.tag=%d", u.i, u.tag);
  }
  printf("\n");
  DestroyDSTable(t); 
}


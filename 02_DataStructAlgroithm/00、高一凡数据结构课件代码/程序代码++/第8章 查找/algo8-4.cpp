// algo8-4.cpp 检验bo8-2.h的程序
#include"c1.h"
#include"func8-5.h" 
#include"c8-2.h" 
typedef ElemType TElemType; 
#include"c6-1.h" 
#include"func8-4.h" 
#include"bo8-2.h" 
void main()
{
  BiTree dt, p;
  int i, n;
  KeyType j;
  ElemType r;
  Status k;
  FILE *f; 
  f=fopen("f8-4.txt", "r"); 
  fscanf(f, "%d", &n); 
  InitDSTable(dt); 
  for(i=0; i<n; i++) 
  { InputFromFile(f, r); 
    k=InsertBST(dt, r); 
    if(!k) 
      printf("二叉排序树dt中已存在关键字为%d的数据，故(%d,%d)无法插入到dt中。\n", 
      r.key, r.key, r.others);
  }
  fclose(f); 
  printf("中序遍历二叉排序树dt：\n");
  TraverseDSTable(dt, Visit); 
  printf("\n先序遍历二叉排序树dt：\n");
  PreOrderTraverse(dt, Visit); 
  printf("\n请输入待查找的关键字的值：");
  InputKey(j); 
  p=SearchBST(dt, j); 
  if(p) 
  { printf("dt中存在关键字为%d的结点。", j);
    DeleteBST(dt, j); 
    printf("删除此结点后，中序遍历二叉排序树dt：\n");
    TraverseDSTable(dt, Visit); 
    printf("\n先序遍历二叉排序树dt：\n");
    PreOrderTraverse(dt, Visit); 
    printf("\n");
  }
  else 
    printf("dt中不存在关键字为%d的结点。\n", j);
  DestroyDSTable(dt); 
}


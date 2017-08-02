// algo8-3.cpp 静态查找表（静态树表）的操作，包括算法9.3和9.4
#include"c1.h"
#include"func8-3.h" 
#include"c8-1.h" 
#include"c8-2.h" 
#include"bo8-1.h" 
typedef ElemType TElemType; 
#include"c6-1.h" 
#include"bo6-1.h" 
#define N 100 
Status SecondOptimal(BiTree &T, ElemType R[], int sw[], int low, int high)
{ 
  int j, i=low; 
  double dw=sw[high]+sw[low-1]; 
  double min=fabs(sw[high]-sw[low]); 
  for(j=low+1; j<=high; j++) 
    if(fabs(dw-sw[j]-sw[j-1])<min) 
    { i=j; 
      min=fabs(dw-sw[j]-sw[j-1]); 
    }
  if(!(T=(BiTree)malloc(sizeof(BiTNode)))) 
    return ERROR;
  T->data=R[i]; 
  if(i==low) 
    T->lchild=NULL; 
  else 
    SecondOptimal(T->lchild, R, sw, low, i-1); 
  if(i==high) 
    T->rchild=NULL; 
  else 
    SecondOptimal(T->rchild, R, sw, i+1, high); 
  return OK;
}
void FindSW(int sw[], SSTable ST)
{ 
  int i;
  sw[0]=0; 
  printf("\nsw=0 ");
  for(i=1; i<=ST.length; i++) 
  { sw[i]=sw[i-1]+ST.elem[i].weight; 
    printf("%5d", sw[i]);
  }
}
typedef BiTree SOSTree; 
void CreateSOSTree(SOSTree &T, SSTable ST)
{ 
  int sw[N+1]; 
  if(ST.length==0) 
    T=NULL; 
  else 
  { FindSW(sw, ST); 
    SecondOptimal(T, ST.elem, sw, 1, ST.length);
    
  }
}
Status Search_SOSTree(SOSTree &T, KeyType key)
{ 
  while(T) 
    if(T->data.key==key) 
      return OK; 
    else if(T->data.key>key) 
      T=T->lchild; 
    else 
      T=T->rchild; 
  return FALSE; 
}
void main()
{
  SSTable st;
  SOSTree t;
  Status i;
  KeyType s;
  Creat_OrdFromFile(st, "f8-3.txt"); 
  printf("       ");
  Traverse(st, Visit); 
  CreateSOSTree(t, st); 
  printf("\n请输入待查找的字符：");
  InputKey(s); 
  i=Search_SOSTree(t, s); 
  if(i) 
    printf("%c的权值是%d\n", s, t->data.weight);
  else 
    printf("表中不存在此字符\n");
  DestroyBiTree(t); 
}


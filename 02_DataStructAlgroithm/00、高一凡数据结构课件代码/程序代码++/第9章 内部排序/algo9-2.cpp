// algo9-2.cpp 表插入排序，包括算法10.3
#include"c1.h"
typedef int KeyType; 
typedef int InfoType; 
#include"c9-1.h" 
#include"c9-3.h" 
typedef SLinkListType SqList; 
#include"func9-2.h" 
void PrintL(SLinkListType L) 
{ int i;
  for(i=0; i<=L.length; i++)
    printf("i=%d key=%d ord=%d next=%d\n", i, L.r[i].rc.key, 
    L.r[i].rc.otherinfo, L.r[i].next);
}
void InputFromFile(FILE* f, RedType &c) 
{ fscanf(f, "%d%d", &c.key, &c.otherinfo);
}
void CreatTableFromFile(SLinkListType &SL, FILE* f)
{ 
  int i;
  fscanf(f, "%d", &SL.length); 
  for(i=1; i<=SL.length; i++)
    InputFromFile(f, SL.r[i].rc); 
}
void MakeTableSorted(SLinkListType &SL)
{ 
  int i, p, q;
  SL.r[0].rc.key=INT_MAX; 
  SL.r[0].next=0; 
  for(i=1; i<=SL.length; i++) 
  { q=0; 
    p=SL.r[0].next; 
    while(SL.r[p].rc.key<=SL.r[i].rc.key) 
    { 
      q=p; 
      p=SL.r[p].next; 
    } 
    SL.r[q].next=i; 
    SL.r[i].next=p;
  }
}
void Arrange(SLinkListType &SL)
{ 
  int i, p, q;
  SLNode t;
  p=SL.r[0].next; 
  for(i=1; i<SL.length; i++)
  { 
    while(p<i) 
      p=SL.r[p].next; 
    q=SL.r[p].next; 
    if(p!=i) 
    { t=SL.r[p]; 
      SL.r[p]=SL.r[i];
      SL.r[i]=t;
      SL.r[i].next=p;
    }
    p=q; 
  }
}
void main()
{
  FILE *f; 
  int *adr, i;
  SLinkListType m1, m2; 
  f=fopen("f9-1.txt", "r"); 
  CreatTableFromFile(m1, f); 
  fclose(f); 
  printf("m1排序前：\n");
  PrintL(m1); 
  MakeTableSorted(m1); 
  m2=m1; 
  printf("m1、m2链式有序后：\n");
  PrintL(m1); 
  Arrange(m1); 
  printf("m1排序后：\n");
  PrintL(m1); 
  adr=(int*)malloc((m2.length+1)*sizeof(int)); 
  Sort(m2, adr); 
  for(i=1; i<=m2.length; i++) 
  { printf("adr[%d]=%d ", i, adr[i]);
    if(i%4==0)
      printf("\n");
  }
  Rearrange(m2, adr); 
  printf("m2排序后：\n");
  PrintL(m2); 
  free(adr); 
}


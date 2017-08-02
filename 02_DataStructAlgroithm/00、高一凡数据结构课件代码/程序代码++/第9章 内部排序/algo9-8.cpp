// algo9-8.cpp 链式基数排序，包括算法10.15～10.17
#include"c1.h"
#include"c9-4.h" 
#include"func9-2.h" 
void MadeListFromFile(SqList &L, FILE* f)
{ 
  int i;
  fscanf(f, "%d", &L.length); 
  L.keynum=0;
  for(i=1; i<=L.length; i++) 
  { fscanf(f, "%s%s", &L.r[i].keys, L.r[i].otheritems);
    L.keynum=__max(unsigned(L.keynum), strlen(L.r[i].keys)); 
  }
  for(i=0; i<L.length; i++) 
    L.r[i].next=i+1;
  L.r[L.length].next=0;
}
int ord(char c)
{
  return c-'`';
}
void Distribute(SLCell r[], int i, ArrType f, ArrType e)
{ 
  
  
  int j, p;
  for(j=0; j<RADIX; j++)
    f[j]=0; 
  for(p=r[0].next; p!=0; p=r[p].next) 
  { if(strlen(r[p].keys)<=unsigned(i)) 
      j=0;
    else
	  j=ord(r[p].keys[i]); 
    if(!f[j]) 
      f[j]=p; 
    else 
      r[e[j]].next=p; 
    e[j]=p; 
  }
}
void Collect(SLCell r[], ArrType f, ArrType e)
{ 
  
  int j, t;
  for(j=0; f[j]==0; j++); 
  r[0].next=f[j]; 
  t=e[j]; 
  while(j<RADIX-1) 
  { for(j++; j<RADIX-1 && f[j]==0; j++); 
    if(f[j]) 
    { r[t].next=f[j]; 
      t=e[j]; 
    }
  }
  r[t].next=0; 
}
void Print2(SqList L)
{ 
  int i=0;
  printf("keynum=%d length=%d i=%d next=%d\n", L.keynum, L.length, i, 
  L.r[i].next);
  for(i=1; i<=L.length; i++)
    printf("i=%d keys=%s otheritems=%s next=%d\n", i, L.r[i].keys, 
    L.r[i].otheritems, L.r[i].next);
}
void PrintLL(SqList L)
{ 
  int i=L.r[0].next;
  while(i)
  { printf("%s ", L.r[i].keys);
    i=L.r[i].next;
  }
  printf("\n");
}
void Printfe(ArrType f, ArrType e)
{ 
  printf("f[j]="); 
  int j;
  for(j=0; j<RADIX; j++)
    printf("%3d", f[j]);
  printf("\ne[j]=");
  for(j=0; j<RADIX; j++)
    if(f[j])
      printf("%3d", e[j]);
    else
      printf("%3d", 0);
  printf("\n");
}
void RadixSort(SqList &L)
{ 
  
  int i;
  ArrType f, e;
  for(i=L.keynum-1; i>=0; i--) 
  { Distribute(L.r, i, f, e); 
    printf("按keys[%d]分配后（只有next域有变化）：\n", i);
    Print2(L); 
    Printfe(f, e); 
    Collect(L.r, f, e); 
    printf("按keys[%d]收集后（只有next域有变化）：\n", i);
    Print2(L); 
    PrintLL(L); 
  }
}
void main()
{
  FILE *f; 
  SqList m; 
  int *adr;
  f=fopen("f9-4.txt", "r"); 
  MadeListFromFile(m, f); 
  fclose(f); 
  printf("排序前：\n");
  Print2(m); 
  RadixSort(m); 
  adr=(int*)malloc((m.length+1)*sizeof(int)); 
  Sort(m, adr); 
  Rearrange(m, adr); 
  free(adr); 
  printf("重排记录后（next域不起作用）：\n");
  Print2(m); 
}


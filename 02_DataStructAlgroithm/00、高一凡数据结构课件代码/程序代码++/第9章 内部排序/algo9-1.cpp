// algo9-1.cpp 检验bo9-1.h的程序
#include"c1.h"
#include"c8-2.h" 
typedef int KeyType; 
typedef int InfoType; 
#include"c9-1.h" 
#include"c9-2.h" 
#include"bo9-1.h" 
#include"func9-1.h" 
void main()
{
  FILE *f; 
  SqList m1, m2, m3, m4; 
  int i;
  f=fopen("f9-1.txt", "r"); 
  fscanf(f, "%d", &m1.length); 
  for(i=1; i<=m1.length; i++) 
    InputFromFile(f, m1.r[i]); 
  fclose(f); 
  m2=m3=m4=m1; 
  printf("排序前：\n");
  Print(m1); 
  InsertSort(m1); 
  printf("直接插入排序后：\n");
  Print(m1); 
  BInsertSort(m2); 
  printf("折半插入排序后：\n");
  Print(m2); 
  P2_InsertSort(m3, 0); 
  printf("2-路插入排序后：\n");
  Print(m3); 
  P2_InsertSort(m4, 1); 
  printf("改进的2-路插入排序后：\n");
  Print(m4); 
}


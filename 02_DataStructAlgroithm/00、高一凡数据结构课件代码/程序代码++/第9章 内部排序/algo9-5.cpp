// algo9-5.cpp �����㷨10.7��10.8��10.6(a)��10.6(b)�ĳ���
#include"c1.h"
typedef int KeyType; 
typedef int InfoType; 
#include"c9-1.h" 
#include"c9-2.h" 
#include"func9-1.h" 
#include"func9-3.h" 
//#include"func9-4.h" // �㷨10.6(b)������Partition()
#include"bo9-2.h" 
void main()
{
  FILE *f; 
  SqList m; 
  int i;
  f=fopen("f9-1.txt", "r"); 
  fscanf(f, "%d", &m.length); 
  for(i=1; i<=m.length; i++) 
    InputFromFile(f, m.r[i]); 
  fclose(f); 
  printf("����ǰ��\n");
  Print(m); 
  QuickSort(m); 
  printf("�����\n");
  Print(m); 
}


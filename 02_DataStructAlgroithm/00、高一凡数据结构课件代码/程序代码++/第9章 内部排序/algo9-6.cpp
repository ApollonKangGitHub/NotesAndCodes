// algo9-6.cpp �����㷨10.9��10.10��10.11�ĳ���
#include"c1.h"
#include"c8-2.h" 
typedef int KeyType; 
typedef int InfoType; 
#include"c9-1.h" 
#include"c9-2.h" 
#include"func9-1.h" 
typedef SqList HeapType; 
#include"bo9-3.h" 
void main()
{
  FILE *f; 
  SqList m1, m2, m3; 
  int i;
  f=fopen("f9-1.txt", "r"); 
  fscanf(f, "%d", &m1.length); 
  for(i=1; i<=m1.length; i++) 
    InputFromFile(f, m1.r[i]); 
  fclose(f); 
  m2=m3=m1; 
  printf("����ǰ��\n");
  Print(m1); 
  SelectSort(m1); 
  printf("��ѡ�������\n");
  Print(m1); 
  HeapSort(m2, TRUE); 
  printf("�󶥶������\n");
  Print(m2); 
  HeapSort(m3, FALSE); 
  printf("С���������\n");
  Print(m3); 
}


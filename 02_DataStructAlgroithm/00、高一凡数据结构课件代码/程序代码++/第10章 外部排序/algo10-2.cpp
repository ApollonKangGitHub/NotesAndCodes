// algo10-2.cpp ������Ĵ��ļ�f10-1.txt����¼����=k*N���ֳ�k������ΪN������С�ļ��ĳ���
#include"c1.h"
#include"c8-2.h" 
typedef int KeyType; 
typedef int InfoType; 
#include"c9-1.h" 
#include"c9-2.h" 
#include"bo9-1.h" 
#include"func9-1.h" 
#define k 5 
#define N 3 
void main()
{
  SqList m; 
  FILE *f, *g; 
  char filename[3]; 
  int i, j;
  f=fopen("f10-1.txt", "r"); 
  for(i=0; i<k; i++) 
  { for(j=1; j<=N; j++) 
      InputFromFile(f, m.r[j]); 
    m.length=N; 
    BInsertSort(m); 
    itoa(i, filename, 10); 
    g=fopen(filename, "w"); 
    printf("�������ļ�%s������Ϊ��", filename);
    Print(m); 
    for(j=1; j<=N; j++) 
      fprintf(g, "%d %d\n", m.r[j].key, m.r[j].otherinfo);
    fclose(g); 
  }
  fclose(f); 
}


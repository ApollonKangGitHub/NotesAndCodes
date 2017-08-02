// algo10-2.cpp 将无序的大文件f10-1.txt（记录个数=k*N）分成k个长度为N的有序小文件的程序
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
    printf("有序子文件%s的数据为：", filename);
    Print(m); 
    for(j=1; j<=N; j++) 
      fprintf(g, "%d %d\n", m.r[j].key, m.r[j].otherinfo);
    fclose(g); 
  }
  fclose(f); 
}


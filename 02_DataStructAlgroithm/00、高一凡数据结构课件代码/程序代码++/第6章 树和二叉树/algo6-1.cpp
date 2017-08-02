// algo6-1.cpp ��շ������롣ʵ���㷨6.12�ĳ���
#include"c1.h"
#include"c6-3.h" 
#include"func6-2.h" 
void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, int* w, int n) 
{ 
  int start;
  unsigned f;
#include"func6-3.h" 
  HC=(HuffmanCode)malloc((n+1)*sizeof(char*));
  
  cd=(char*)malloc(n*sizeof(char)); 
  cd[n-1]='\0'; 
  for(i=1; i<=n; i++)
  { 
    start=n-1; 
    for(c=i, f=HT[i].parent; f!=0; c=f, f=HT[f].parent) 
      if(HT[f].lchild==c) 
        cd[--start]='0'; 
      else 
        cd[--start]='1'; 
    HC[i]=(char*)malloc((n-start)*sizeof(char)); 
    strcpy(HC[i], &cd[start]); 
  }
  free(cd); 
}
#include"func6-4.h" 


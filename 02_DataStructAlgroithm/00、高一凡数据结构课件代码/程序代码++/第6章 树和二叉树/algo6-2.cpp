// algo6-2.cpp 实现算法6.13的程序
#include"c1.h"
#include"c6-3.h" 
#include"func6-2.h" 
void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, int* w, int n)
// 前半部分为算法6.12的前半部分
{ 
  unsigned cdlen;
#include"func6-3.h" 
  
  HC=(HuffmanCode)malloc((n+1)*sizeof(char*));
  
  cd=(char*)malloc(n*sizeof(char)); 
  c=m; 
  cdlen=0; 
  for(i=1; i<=m; i++)
    HT[i].weight=0;
  while(c) 
  { if(HT[c].weight==0) 
    { 
      HT[c].weight=1; 
      if(HT[c].lchild!=0) 
      { c=HT[c].lchild; 
        cd[cdlen++]='0'; 
      }
      else if(HT[c].rchild==0) 
      { 
        HC[c]=(char*)malloc((cdlen+1)*sizeof(char)); 
        cd[cdlen]='\0'; 
        strcpy(HC[c], cd); 
      }
    }
    else if(HT[c].weight==1) 
    { 
      HT[c].weight=2; 
      if(HT[c].rchild!=0) 
      { c=HT[c].rchild; 
        cd[cdlen++]='1'; 
      }
    }
    else 
    { c=HT[c].parent; 
      --cdlen; 
    }
  }
  free(cd); 
}
#include"func6-4.h" 


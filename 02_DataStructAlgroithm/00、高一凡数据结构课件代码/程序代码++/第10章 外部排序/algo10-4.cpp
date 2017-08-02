// algo10-4.cpp 通过置换-选择排序产生不等长的初始归并段文件
#include"c1.h"
typedef int KeyType; 
typedef int InfoType; 
#include"c9-1.h" 
#define MAX_KEY INT_MAX 
#define w 6 
#define M 10 
typedef int LoserTree[w];
// [1～w-1]是败者树的非叶子结点，[0]中是胜者，存相应叶子的序号
typedef struct
{ RedType rec; 
  int rnum; 
}WorkArea[w]; 
void InputFromFile(FILE* f, RedType &c)
{ 
  fscanf(f, "%d%d", &c.key, &c.otherinfo);
}
void OutputToFile(FILE* f, RedType &c)
{ 
  fprintf(f, "%d %d\n", c.key, c.otherinfo);
}
void Select_MiniMax(LoserTree ls, WorkArea wa, int q) 
{ 
  int s, p, t=(w+q)/2; 
  for(p=ls[t]; t>0; t=t/2, p=ls[t]) 
    if(wa[p].rnum<wa[q].rnum||wa[p].rnum==wa[q].rnum&&
    wa[p].rec.key<wa[q].rec.key) 
    { s=q; 
      q=ls[t]; 
      ls[t]=s;
    }
  ls[0]=q; 
}
void Construct_Loser(LoserTree ls, WorkArea wa, FILE *fi)
{ 
  
  int i;
  for(i=0; i<w; i++)
    wa[i].rnum=ls[i]=0; 
  for(i=w-1; i>=0; i--) 
  { InputFromFile(fi, wa[i].rec); 
    wa[i].rnum=1; 
    Select_MiniMax(ls, wa, i); 
  }
}
void get_run(LoserTree ls, WorkArea wa, int rc, int &rmax, FILE *fi, FILE *fo)
{ 
  int q;
  KeyType minimax;
  while(wa[ls[0]].rnum==rc) 
  { q=ls[0]; 
    minimax=wa[q].rec.key; 
    OutputToFile(fo, wa[q].rec); 
    printf("(%d,%d)", wa[q].rec.key, wa[q].rec.otherinfo); 
    InputFromFile(fi, wa[q].rec); 
    if(feof(fi)) 
      wa[q].rnum=rmax+1; 
    else 
    { if(wa[q].rec.key<minimax)
      { 
        rmax=rc+1; 
        wa[q].rnum=rmax; 
      }
      else 
        wa[q].rnum=rc;
    }
    Select_MiniMax(ls, wa, q); 
  }
}
void Replace_Selection(LoserTree ls, WorkArea wa, FILE *fi)
{ 
  
  int rc, rmax;
  FILE *fo; 
  char filename[3]; 
  Construct_Loser(ls, wa, fi); 
  rc=rmax=1; 
  do 
  { itoa(rc-1, filename, 10); 
    fo=fopen(filename, "w"); 
    printf("%s的内容为：", filename);
    get_run(ls, wa, rc, rmax, fi, fo); 
    printf("\n");
    fclose(fo); 
    rc=wa[ls[0]].rnum; 
  }while(rc<=rmax); 
  printf("共产生%d个初始归并段文件\n", rc-1);
}
void main()
{
  FILE *fi;
  LoserTree ls;
  WorkArea wa;
  fi=fopen("f10-2.txt", "r"); 
  Replace_Selection(ls, wa, fi); 
  fclose(fi); 
}


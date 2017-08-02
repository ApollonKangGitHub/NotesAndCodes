// algo10-3.cpp 调用bo10-1.h的程序（运行algo10-2.cpp后运行此程序）
#include"c1.h"
typedef int KeyType; 
typedef int InfoType; 
#include"c9-1.h" 
#define k 5 
//#define k 3 // 3路归并。第7行
FILE *fp[k+1]; 
typedef int LoserTree[k];
// [1～k-1]是败者树的非叶子结点，[0]中是胜者，存相应叶子的序号
RedType b[k+1]; 
#define MIN_KEY INT_MIN 
#define MAX_KEY INT_MAX 
#define M 10 
void Print(RedType t)
{ printf("(%d, %d)", t.key, t.otherinfo);
}
#include"bo10-1.h" 
void main()
{
  LoserTree ls; 
  int i;
  char outfile[10], filename[3]; 
  for(i=0; i<k; i++)
  { itoa(i, filename, 10); 
    fp[i]=fopen(filename, "r"); 
  }
  printf("请输入排序后的大文件名：");
  scanf("%s", outfile); 
  fp[k]=fopen(outfile, "w"); 
  printf("有序大文件%s的记录为：\n", outfile);
  K_Merge(ls); 
  printf("\n"); 
  for(i=0; i<=k; i++)
    fclose(fp[i]); 
}


// algo2-4.cpp 严书中图2.10静态链表示例
// 第1个结点的位置在[0].cur中。成员cur的值为0，则到链表尾
#include"c1.h"
#define N 6 
typedef char ElemType[N]; 
#include"c2-3.h" 
void main()
{
  SLinkList s={{"",1},{"ZHAO",2},{"QIAN",3},{"SUN",4},{"LI",5},{"ZHOU",6},
               {"WU",7},{"ZHENG",8},{"WANG",0}}; 
  int i=s[0].cur; 
  while(i) 
  { 
    printf("%s ", s[i].data); 
    i=s[i].cur; 
  }
  printf("\n");
  s[4].cur=9; 
  s[9].cur=5;
  strcpy(s[9].data, "SHI");
  s[6].cur=8; 
  i=s[0].cur; 
  while(i) 
  { 
    printf("%s ", s[i].data); 
    i=s[i].cur; 
  }
  printf("\n");
}


// algo2-4.cpp ������ͼ2.10��̬����ʾ��
// ��1������λ����[0].cur�С���Աcur��ֵΪ0��������β
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


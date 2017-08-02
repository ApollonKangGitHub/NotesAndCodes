// algo3-1.cpp 调用算法3.1的程序
#define N 8 
typedef int SElemType; 
#include"c1.h"
#include"c3-1.h" 
#include"bo3-1.h" 
void conversion() 
{ 
  SqStack s;
  unsigned n; 
  SElemType e;
  InitStack(s); 
  printf("将十进制整数n转换为%d进制数，请输入：n（≥0）=", N);
  scanf("%u", &n); 
  while(n) 
  { Push(s, n%N); 
    n=n/N;
  }
  while(!StackEmpty(s)) 
  { Pop(s, e); 
    printf("%d", e); 
  }
  printf("\n");
}
void main()
{
  conversion();
}


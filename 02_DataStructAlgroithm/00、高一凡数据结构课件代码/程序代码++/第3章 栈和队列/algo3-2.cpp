// algo3-2.cpp �޸��㷨3.1��ʮ���ơ�ʮ������
typedef int SElemType; 
#include"c1.h"
#include"c3-1.h" 
#include"bo3-1.h" 
void conversion()
{ 
  SqStack s;
  unsigned n; 
  SElemType e;
  printf("��ʮ��������nת��Ϊʮ���������������룺n����0��=");
  scanf("%u", &n); 
  InitStack(s); 
  while(n) 
  { Push(s, n%16); 
    n=n/16;
  }
  while(!StackEmpty(s)) 
  { Pop(s, e); 
    if(e<=9)
      printf("%d", e); 
    else
      printf("%c", e+55); 
  }
  printf("\n");
  DestroyStack(s);
}
void main()
{
  conversion();
}


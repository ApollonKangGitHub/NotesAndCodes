// main3-1.cpp ����bo3-1.h��������
#include"c1.h"
typedef int SElemType; 
#include"c3-1.h" 
#include"bo3-1.h" 
#define ElemType SElemType 
#include"func2-2.h" 
void main()
{
  int j;
  SqStack s;
  SElemType e;
  InitStack(s); 
  for(j=1; j<=12; j++)
    Push(s, j); 
  printf("ջ��Ԫ������Ϊ");
  StackTraverse(s, print); 
  Pop(s, e); 
  printf("������ջ��Ԫ��e=%d\n", e);
  printf("ջ�շ�%d��1���� 0���񣩣�", StackEmpty(s));
  GetTop(s, e); 
  printf("ջ��Ԫ��e=%d��ջ�ĳ���Ϊ%d\n", e, StackLength(s));
  ClearStack(s); 
  printf("���ջ��ջ�շ�%d��1���� 0����\n", StackEmpty(s));
  DestroyStack(s); 
  printf("����ջ��s.top=%u��s.base=%u��s.stacksize=%d\n", s.top, s.base, 
  s.stacksize);
}


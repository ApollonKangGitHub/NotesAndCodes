// algo3-5.cpp ���ʽ��ֵ�������ֵ��0��9֮�䣬�м����������ֵ��-128��127֮�䣩��
// �㷨3.4
typedef char SElemType; 
#include"c1.h"
#include"c3-1.h" 
#include"bo3-1.h" 
#include"func3-1.h" 
SElemType EvaluateExpression() 
{ 
  SqStack OPTR, OPND;
  SElemType a, b, c, x;
  InitStack(OPTR); 
  InitStack(OPND);
  Push(OPTR, '\n'); 
  c=getchar(); 
  GetTop(OPTR, x); 
  while(c!='\n' || x!='\n') 
  { if(In(c)) 
      switch(Precede(x, c)) 
      { case'<': Push(OPTR, c); 
                 c=getchar(); 
                 break;
        case'=': Pop(OPTR, x); 
                 c=getchar(); 
                 break;
        case'>': Pop(OPTR,x);
                 Pop(OPND, b); 
                 Pop(OPND, a);
                 Push(OPND, Operate(a, x, b));
      }
    else if(c>='0' && c<='9') 
    { Push(OPND, c-48); 
      c=getchar(); 
    }
    else 
    { printf("���ַǷ��ַ�\n");
      exit(OVERFLOW);
    }
    GetTop(OPTR, x); 
  }
  Pop(OPND, x); 
  if(!StackEmpty(OPND)) 
  { printf("���ʽ����ȷ\n");
    exit(OVERFLOW);
  }
  return x;
}
void main()
{
  printf("�������������ʽ�������ֵҪ��0��9֮�䡢");
  printf("�м�����ֵ����������-128��127֮�䣩\n");
  printf("%d\n", EvaluateExpression()); 
}


// algo3-5.cpp 表达式求值（输入的值在0～9之间，中间结果和输出的值在-128～127之间），
// 算法3.4
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
    { printf("出现非法字符\n");
      exit(OVERFLOW);
    }
    GetTop(OPTR, x); 
  }
  Pop(OPND, x); 
  if(!StackEmpty(OPND)) 
  { printf("表达式不正确\n");
    exit(OVERFLOW);
  }
  return x;
}
void main()
{
  printf("请输入算术表达式（输入的值要在0～9之间、");
  printf("中间运算值和输出结果在-128～127之间）\n");
  printf("%d\n", EvaluateExpression()); 
}


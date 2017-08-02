// algo3-6.cpp 表达式求值（范围为int类型，输入负数要用（0-正数）表示）
typedef int SElemType; 
#include"c1.h"
#include"c3-1.h" 
#include"bo3-1.h" 
#include"func3-1.h" 
SElemType EvaluateExpression()
{ 
  SqStack OPTR, OPND;
  SElemType a, b, d, x; 
  char c; 
  c=getchar(); 
  InitStack(OPTR); 
  InitStack(OPND);
  Push(OPTR, '\n'); 
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
        case'>': Pop(OPTR, x); 
                 Pop(OPND, b); 
                 Pop(OPND, a);
                 Push(OPND, Operate(a, x, b)); 
      }
    else if(c>='0' && c<='9') 
    { d=0;
      while(c>='0' && c<='9') 
      { d=d*10+c-'0';
        c=getchar();
      }
      Push(OPND, d); 
    }
    else 
    { printf("出现非法字符\n");
      DestroyStack(OPTR);
      DestroyStack(OPND);
      exit(OVERFLOW);
    }
    GetTop(OPTR, x); 
  }
  Pop(OPND, x); 
  if(!StackEmpty(OPND)) 
  { printf("表达式不正确\n");
    DestroyStack(OPTR);
    DestroyStack(OPND);
    exit(OVERFLOW);
  }
  DestroyStack(OPTR);
  DestroyStack(OPND);
  return x;
}
void main()
{
  printf("请输入算术表达式，负数要用（0-正数）表示\n");
  printf("%d\n", EvaluateExpression());
}


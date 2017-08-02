// func3-1.h algo3-5.cpp��algo3-6.cppҪ���õĺ���
char Precede(SElemType t1, SElemType t2)
{ 
  char f;
  switch(t2)
  { case '+':
    case '-': if(t1=='(' || t1=='\n')
                f='<'; 
              else
                f='>'; 
              break;
    case '*':
    case '/': if(t1=='*' || t1=='/' || t1==')')
                f='>'; 
              else
                f='<'; 
              break;
    case '(': if(t1==')')
              { printf("���Ų�ƥ��\n");
                exit(OVERFLOW);
              }
              else
                f='<'; 
              break;
    case ')': switch(t1)
              { case '(': f='='; 
                          break;
                case'\n': printf("ȱ��������\n");
                          exit(OVERFLOW);
                default : f='>'; 
              }
              break;
    case'\n': switch(t1)
              { case'\n': f='='; 
                          break;
                case '(': printf("ȱ��������\n");
                          exit(OVERFLOW);
                default : f='>'; 
              }
  }
  return f;
}
Status In(SElemType c)
{ 
  switch(c)
  { case '+':
    case '-':
    case '*':
    case '/':
    case '(':
    case ')':
    case'\n': return TRUE;
    default : return FALSE;
  }
}
SElemType Operate(SElemType a, SElemType theta, SElemType b)
{ 
  switch(theta)
  { case '+': return a+b;
    case '-': return a-b;
    case '*': return a*b;
  }
  return a/b; 
}


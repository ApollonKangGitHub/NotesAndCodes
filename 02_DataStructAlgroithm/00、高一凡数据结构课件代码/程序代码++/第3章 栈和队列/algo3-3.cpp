// algo3-3.cpp �б༭����ʵ���㷨3.2
typedef char SElemType; 
#include"c1.h"
#include"c3-1.h" 
#include"bo3-1.h" 
FILE *fp;
void copy(SElemType c)
{ 
  fputc(c, fp);
}
void LineEdit()
{ 
  SqStack s;
  char ch;
  InitStack(s); 
  printf("������һ���ı��ļ���^Z�������룺\n");
  ch=getchar(); 
  while(ch!=EOF) 
  { while(ch!=EOF && ch!='\n') 
    { switch(ch) 
      { case '#': if(!StackEmpty(s))
                    Pop(s, ch); 
                  break;
        case '@': ClearStack(s); 
                  break;
        default : Push(s, ch); 
      }
      ch=getchar(); 
    } 
    StackTraverse(s, copy);
    fputc('\n', fp); 
    ClearStack(s); 
    if(ch!=EOF) 
      ch=getchar(); 
  }
  DestroyStack(s); 
}
void main()
{
  fp=fopen("ed.txt", "w");
  
  if(fp) 
  { LineEdit(); 
    fclose(fp); 
  }
  else
    printf("�����ļ�ʧ�ܣ�\n");
}


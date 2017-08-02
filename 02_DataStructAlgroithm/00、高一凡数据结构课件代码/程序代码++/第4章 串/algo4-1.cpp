// algo4-1.cpp 实现算法4.6～4.8的程序
#include"c1.h"
#include"c4-1.h" 
#include"bo4-1.h" 
void get_next(SString T, int next[])
{ 
  int i=1, j=0;
  next[1]=0; 
  while(i<T[0]) 
    if(j==0 || T[i]==T[j]) 
    { i++; 
      j++;
      next[i]=j; 
    }
    else 
      j=next[j]; 
}
void get_nextval(SString T, int nextval[])
{ 
  int i=1, j=0;
  nextval[1]=0;
  while(i<T[0])
    if(j==0 || T[i]==T[j]) 
    { i++; 
      j++;
      if(T[i]!=T[j]) 
        nextval[i]=j;
      else
        nextval[i]=nextval[j];
    }
    else
      j=nextval[j]; 
}
int Index_KMP(SString S, SString T, int pos, int next[])
{ 
  
  int i=pos, j=1; 
  while(i<=S[0] && j<=T[0]) 
    if(j==0 || S[i]==T[j]) 
    { i++;
      j++;
    }
    else 
      j=next[j];
  if(j>T[0]) 
    return i-T[0];
  else
    return 0;
}
void main()
{
  int i, *p;
  SString s1, s2; 
  StrAssign(s1, "aaabaaaab"); 
  printf("主串为");
  StrPrint(s1); 
  StrAssign(s2, "aaaab"); 
  printf("子串为");
  StrPrint(s2); 
  p=(int*)malloc((StrLength(s2)+1)*sizeof(int)); 
  get_next(s2, p); 
  printf("子串的next数组为");
  for(i=1; i<=StrLength(s2); i++)
    printf("%d ", *(p+i));
  printf("\n");
  i=Index_KMP(s1, s2, 1, p); 
  if(i)
    printf("主串和子串在第%d个字符处首次匹配\n", i);
  else
    printf("主串和子串匹配不成功\n");
  get_nextval(s2, p); 
  printf("子串的nextval数组为");
  for(i=1; i<=StrLength(s2); i++)
    printf("%d ", *(p+i));
  printf("\n");
  printf("主串和子串在第%d个字符处首次匹配\n", Index_KMP(s1, s2, 1, p));
}


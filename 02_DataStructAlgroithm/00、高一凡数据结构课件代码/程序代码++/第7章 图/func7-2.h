// func7-2.h 包括弧的相关信息类型的定义及对它的操作
#define MAX_INFO 20 
typedef char InfoType; 
void InputArc(InfoType* &arc) 
{ char s[MAX_INFO]; 
  int m;
  printf("请输入该弧的相关信息（<%d个字符）：", MAX_INFO);
  gets(s); 
  m=strlen(s); 
  if(m) 
  { arc=(char*)malloc((m+1)*sizeof(char)); 
    strcpy(arc, s); 
  }
}
void InputArcFromFile(FILE* f, InfoType* &arc) 
{ char s[MAX_INFO]; 
  fgets(s, MAX_INFO, f); 
  arc=(char*)malloc((strlen(s)+1)*sizeof(char)); 

  strcpy(arc, s); 
}
void OutputArc(InfoType* arc) 
{ printf("%s\n", arc);
}


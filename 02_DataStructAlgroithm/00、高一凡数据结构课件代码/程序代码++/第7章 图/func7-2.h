// func7-2.h �������������Ϣ���͵Ķ��弰�����Ĳ���
#define MAX_INFO 20 
typedef char InfoType; 
void InputArc(InfoType* &arc) 
{ char s[MAX_INFO]; 
  int m;
  printf("������û��������Ϣ��<%d���ַ�����", MAX_INFO);
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


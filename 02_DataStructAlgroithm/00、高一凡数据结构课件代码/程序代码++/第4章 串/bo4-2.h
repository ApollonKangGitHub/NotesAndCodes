// bo4-2.h 串采用堆分配存储结构（由c4-2.h定义）的基本操作（12个）。包括算法4.4
#define DestroyString ClearString 
void InitString(HString &S)
{ 
  S.length=0;
  S.ch=NULL;
}
void ClearString(HString &S)
{ 
  free(S.ch); 
  InitString(S); 
}
void StrAssign(HString &T, char* chars)
{ 
  int i, j;
  if(T.ch) 
    free(T.ch); 
  i=strlen(chars); 
  if(!i) 
    InitString(T); 
  else 
  { T.ch=(char*)malloc(i*sizeof(char)); 
    if(!T.ch) 
      exit(OVERFLOW);
    for(j=0; j<i; j++) 
      T.ch[j]=chars[j];
    T.length=i; 
  }
}
void StrCopy(HString &T, HString S)
{ 
  int i;
  if(T.ch) 
    free(T.ch); 
  T.ch=(char*)malloc(S.length*sizeof(char)); 
  if(!T.ch) 
    exit(OVERFLOW);
  for(i=0; i<S.length; i++) 
    T.ch[i]=S.ch[i]; 
  T.length=S.length; 
}
Status StrEmpty(HString S)
{ 
  if(S.length==0 && S.ch==NULL) 
    return TRUE;
  else
    return FALSE;
}
int StrCompare(HString S, HString T)
{ 
  int i;
  for(i=0; i<S.length && i<T.length; i++) 
    if(S.ch[i]!=T.ch[i]) 
      return S.ch[i]-T.ch[i]; 
  return S.length-T.length; 
}
int StrLength(HString S)
{ 
  return S.length;
}
void Concat(HString &T, HString S1, HString S2)
{ 
  int i;
  if(T.ch) 
    free(T.ch); 
  T.length=S1.length+S2.length; 
  T.ch=(char*)malloc(T.length*sizeof(char)); 
  if(!T.ch) 
    exit(OVERFLOW);
  for(i=0; i<S1.length; i++) 
    T.ch[i]=S1.ch[i];
  for(i=0; i<S2.length; i++) 
    T.ch[S1.length+i]=S2.ch[i];
}
Status SubString(HString &Sub, HString S, int pos, int len)
{ 
  
  int i;
  if(pos<1 || pos>S.length || len<0 || len>S.length-pos+1) 
    return ERROR; 
  if(Sub.ch) 
    free(Sub.ch); 
  if(!len) 
    InitString(Sub); 
  else 
  { Sub.ch=(char*)malloc(len*sizeof(char)); 
    if(!Sub.ch) 
      exit(OVERFLOW);
    for(i=0; i<=len-1; i++) 
      Sub.ch[i]=S.ch[pos-1+i];
    Sub.length=len; 
  }
  return OK;
}
Status StrInsert(HString &S, int pos, HString T) 
{ 
  int i;
  if(pos<1 || pos>S.length+1) 
    return ERROR;
  if(T.length) 
  { S.ch=(char*)realloc(S.ch, (S.length+T.length)*sizeof(char));
    if(!S.ch) 
      exit(OVERFLOW);
    for(i=S.length-1; i>=pos-1; --i) 
      S.ch[i+T.length]=S.ch[i];
    for(i=0; i<T.length; i++) 
      S.ch[pos-1+i]=T.ch[i];
    S.length+=T.length; 
  }
  return OK;
}
Status StrDelete(HString &S, int pos, int len)
{ 
  int i;
  if(S.length<pos+len-1) 
    return ERROR;
  for(i=pos-1; i<=S.length-len; i++) 
    S.ch[i]=S.ch[i+len];
  S.length-=len; 
  S.ch=(char*)realloc(S.ch, S.length*sizeof(char));
  return OK;
}
void StrPrint(HString S)
{ 
  int i;
  for(i=0; i<S.length; i++)
    printf("%c", S.ch[i]);
  printf("\n");
}


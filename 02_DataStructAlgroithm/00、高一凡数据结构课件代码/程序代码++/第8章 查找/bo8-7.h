// bo8-7.h 哈希函数的基本操作，包括算法9.17、9.18
void InitHashTable(HashTable &H)
{ 
  int i;
  H.count=0; 
  H.sizeindex=0; 
  m=hashsize[0]; 
  H.elem=(ElemType*)malloc(m*sizeof(ElemType));
  if(!H.elem)
    exit(OVERFLOW); 
  for(i=0; i<m; i++)
    H.elem[i].key=NULL_KEY; 
}
void DestroyHashTable(HashTable &H)
{ 
  free(H.elem); 
  H.elem=NULL;
  H.count=0;
  H.sizeindex=0;
}
unsigned Hash(KeyType K)
{ 
  return K%m;
}
int d(int i) 
{ return i; 
//return ((i+1)/2)*((i+1)/2)*(int)pow(-1, i-1); // 二次探测再散列
//return rand(); // 伪随机探测再散列
}
void collision(KeyType K, int &p, int i)
{ p=(Hash(K)+d(i))%m; 
}
Status SearchHash(HashTable H, KeyType K, int &p, int &c)
{ 
  
  
  c=0;
  p=Hash(K); 
  while(H.elem[p].key!=NULL_KEY && !EQ(K, H.elem[p].key))
  { 
    c++; 
    if(c<m) 
      collision(K, p, c); 
    else 
      break; 
  }
  if EQ(K, H.elem[p].key) 
    return SUCCESS; 
  else 
    return UNSUCCESS; 
}
void RecreateHashTable(HashTable&); 
Status InsertHash(HashTable &H, ElemType e)
{ 
  
  int p, c=0; 
  if(SearchHash(H, e.key, p, c)) 
    return DUPLICATE; 
  else if(c<hashsize[H.sizeindex]/2) 
  { H.elem[p]=e; 
    ++H.count; 
    return OK; 
  }
  else 
  { RecreateHashTable(H); 
    return UNSUCCESS; 
  }
}
void RecreateHashTable(HashTable &H)
{ 
  int i, count=H.count; 
  ElemType *p, *elem=(ElemType*)malloc(count*sizeof(ElemType));
  
  p=elem; 
  for(i=0; i<m; i++) 
    if((H.elem+i)->key!=NULL_KEY) 
      *p++=*(H.elem+i); 
  H.count=0; 
  H.sizeindex++; 
  m=hashsize[H.sizeindex]; 
  H.elem=(ElemType*)realloc(H.elem, m*sizeof(ElemType));
  
  for(i=0; i<m; i++)
    H.elem[i].key=NULL_KEY; 
  for(p=elem; p<elem+count; p++) 
    InsertHash(H, *p);
  free(elem); 
}
void TraverseHash(HashTable H, void(*Visit)(int, ElemType))
{ 
  int i;
  printf("哈希地址0～%d\n", m-1);
  for(i=0; i<m; i++) 
    if(H.elem[i].key!=NULL_KEY) 
      Visit(i, H.elem[i]); 
}


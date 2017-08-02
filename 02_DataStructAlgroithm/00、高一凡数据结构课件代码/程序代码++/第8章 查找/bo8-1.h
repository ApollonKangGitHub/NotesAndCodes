// bo8-1.h 静态查找表（顺序表和有序表）的基本操作（7个），包括算法9.1和9.2
void Creat_SeqFromFile(SSTable &ST, char* filename)
{ 
  int i;
  FILE *f; 
  f=fopen(filename, "r"); 
  fscanf(f, "%d", &ST.length); 
  ST.elem=(ElemType*)calloc(ST.length+1, sizeof(ElemType));
  
  if(!ST.elem) 
    exit(OVERFLOW);
  for(i=1; i<=ST.length; i++)
    InputFromFile(f, ST.elem[i]);
    
  fclose(f); 
}
void Ascend(SSTable &ST)
{ 
  int i, j, k;
  for(i=1; i<ST.length; i++)
  { k=i; 
    ST.elem[0]=ST.elem[i]; 
    for(j=i+1; j<=ST.length; j++) 
      if LT(ST.elem[j].key, ST.elem[0].key) 
      { k=j; 
        ST.elem[0]=ST.elem[j]; 
      }
    if(k!=i) 
    { ST.elem[k]=ST.elem[i];
      ST.elem[i]=ST.elem[0];
    }
  }
}
void Creat_OrdFromFile(SSTable &ST, char* filename)
{ 
  Creat_SeqFromFile(ST, filename); 
  Ascend(ST); 
}
Status Destroy(SSTable &ST)
{ 
  free(ST.elem); 
  ST.elem=NULL; 
  ST.length=0; 
  return OK;
}
int Search_Seq(SSTable ST, KeyType key)
{ 
  
  int i;
  ST.elem[0].key=key; 
  for(i=ST.length; !EQ(ST.elem[i].key, key); --i); 
  return i; 
}
int Search_Bin(SSTable ST, KeyType key)
{ 
  
  int mid, low=1, high=ST.length; 
  while(low<=high) 
  { mid=(low+high)/2; 
    if EQ(key, ST.elem[mid].key) 
      return mid; 
    else if LT(key, ST.elem[mid].key) 
      high=mid-1; 
    else
      low=mid+1; 
  }
  return 0; 
}
void Traverse(SSTable ST, void(*Visit)(ElemType))
{ 
  
  int i;
  ElemType *p=++ST.elem; 
  for(i=1; i<=ST.length; i++) 
    Visit(*p++); 
}


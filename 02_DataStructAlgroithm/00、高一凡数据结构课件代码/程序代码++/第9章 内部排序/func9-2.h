// func9-2.h °üÀ¨Ëã·¨10.18
void Sort(SqList L, int adr[])
{ 
  int i=1, p=L.r[0].next; 
  while(p) 
  { adr[i++]=p; 
    p=L.r[p].next; 
  }
}
void Rearrange(SqList &L, int adr[])
{ 
  
  int i, j, k;
  for(i=1; i<L.length; i++) 
    if(adr[i]!=i) 
    { j=i;
      L.r[0]=L.r[i]; 
      while(adr[j]!=i) 
      { 
        k=adr[j];
        L.r[j]=L.r[k]; 
        adr[j]=j; 
        j=k; 
      }
      L.r[j]=L.r[0]; 
      adr[j]=j;
    }
}


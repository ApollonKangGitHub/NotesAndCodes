// bo9-1.h 顺序表插入排序的函数（3个），包括算法10.1和算法10.2
void InsertSort(SqList &L)
{ 
  int i, j;
  for(i=2; i<=L.length; i++) 
    if LT(L.r[i].key, L.r[i-1].key) 
    { 
      L.r[0]=L.r[i]; 
      for(j=i-1; LT(L.r[0].key, L.r[j].key); j--) 
        L.r[j+1]=L.r[j]; 
      L.r[j+1]=L.r[0]; 
    }
}
void BInsertSort(SqList &L)
{ 
  int i, j, m, low, high;
  for(i=2; i<=L.length; i++) 
    if LT(L.r[i].key, L.r[i-1].key) 
    { 
      L.r[0]=L.r[i]; 
      low=1; 
      high=i-1; 
      while(low<=high) 
      { m=(low+high)/2; 
        if LT(L.r[0].key, L.r[m].key) 
          high=m-1; 
        else 
          low=m+1; 
      } 
      for(j=i-1; j>=high+1; j--) 
        L.r[j+1]=L.r[j]; 
      L.r[high+1]=L.r[0]; 
    }
}
void P2_InsertSort(SqList &L, int flag)
{ 
  
  int i, j, first, final, mid=0;
  RedType *d;
  d=(RedType*)malloc(L.length*sizeof(RedType)); 
  d[0]=L.r[1]; 
  first=final=0; 
  for(i=2; i<=L.length; i++) 
  { if(flag) 
    { if(first>final)
        j=L.length; 
      else
        j=0;
      mid=(first+final+j)/2%L.length; 
    }
    if(L.r[i].key<d[mid].key) 
    { j=first; 
      first=(first-1+L.length)%L.length; 
      while(L.r[i].key>d[j].key) 
      { d[(j-1+L.length)%L.length]=d[j]; 
        j=(j+1)%L.length; 
      }
      d[(j-1+L.length)%L.length]=L.r[i]; 
    }
    else 
    { j=final++; 
      while(L.r[i].key<d[j].key) 
      { d[(j+1)%L.length]=d[j]; 
        j=(j-1+L.length)%L.length; 
      }
      d[(j+1)%L.length]=L.r[i]; 
    }
  }
  for(i=1; i<=L.length; i++) 
    L.r[i]=d[(first+i-1)%L.length]; 
  free(d); 
}


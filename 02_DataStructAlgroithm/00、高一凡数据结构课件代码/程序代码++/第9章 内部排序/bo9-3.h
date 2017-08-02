// bo9-3.h 选择排序算法，包括算法10.9、10.10和10.11
int SelectMinKey(SqList L, int i)
{ 
  int j, k=i; 
  KeyType min=L.r[i].key; 
  for(j=i+1; j<=L.length; j++) 
    if(L.r[j].key<min) 
    { k=j; 
      min=L.r[j].key;
    }
  return k; 
}
void SelectSort(SqList &L)
{ 
  int i, j;
  RedType t;
  for(i=1; i<L.length; i++) 
  { j=SelectMinKey(L, i); 
    if(i!=j)
    { t=L.r[i]; 
      L.r[i]=L.r[j];
      L.r[j]=t;
    }
  }
}
void HeapAdjust(HeapType &H, int s, int m, Boolean flag)
{ 
  
  int j;
  H.r[0]=H.r[s]; 
  for(j=2*s; j<=m; j*=2) 
  { if(flag) 
    { if(j<m && LT(H.r[j].key, H.r[j+1].key)) 
        j++; 
      if(!LT(H.r[0].key, H.r[j].key)) 
        break; 
    }
    else 
    { if(j<m && GT(H.r[j].key, H.r[j+1].key)) 
        j++; 
      if(!GT(H.r[0].key, H.r[j].key)) 
        break; 
    }
    H.r[s]=H.r[j]; 
    s=j; 
  }
  H.r[s]=H.r[0]; 
}
void HeapSort(HeapType &H, Boolean flag)
{ 
  
  int i;
  for(i=H.length/2; i>0; i--) 
    HeapAdjust(H, i, H.length, flag); 
  for(i=H.length; i>1; i--)
  { H.r[0]=H.r[1]; 
    H.r[1]=H.r[i];
    H.r[i]=H.r[0];
    HeapAdjust(H, 1, i-1, flag); 
  }
}


// func9-3.h Ëã·¨10.6(a)
int Partition(SqList &L, int low, int high)
{ 
  
  RedType t;
  KeyType pivotkey; 
  pivotkey=L.r[low].key; 
  while(low<high) 
  { 
    while(low<high && L.r[high].key>=pivotkey) 
      high--; 
    t=L.r[low]; 
    L.r[low]=L.r[high];
    L.r[high]=t;
    while(low<high && L.r[low].key<=pivotkey) 
      low++; 
    t=L.r[low]; 
    L.r[low]=L.r[high];
    L.r[high]=t;
  }
  return low; 
}


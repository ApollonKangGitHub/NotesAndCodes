// bo9-2.h ��������ĺ����������㷨10.7��10.8
void QSort(SqList &L, int low, int high)
{ 
  int pivotloc;
  if(low<high) 
  { pivotloc=Partition(L, low, high);
    
    QSort(L, low, pivotloc-1); 
    QSort(L, pivotloc+1, high); 
  }
}
void QuickSort(SqList &L)
{ 
  QSort(L, 1, L.length); 
}


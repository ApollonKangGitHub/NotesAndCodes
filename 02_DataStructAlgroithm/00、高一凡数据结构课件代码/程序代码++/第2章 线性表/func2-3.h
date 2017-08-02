// func2-3.h 检验单链表基本操作的主函数
// main2-2.cpp、main2-3.cpp、main2-4.cpp和main2-5.cpp调用
void main()
{
  LinkList L; 
  ElemType e, e0;
  Status i;
  int j, k;
  InitList(L); 
  for(j=1; j<=5; j++)
    i=ListInsert(L, 1, j); 
  printf("在L的表头依次插入1～5后，L=");
  ListTraverse(L, print); 
  i=ListEmpty(L); 
  printf("L是否空？i=%d（1：是 0：否），表L的长度=%d\n", i, ListLength(L));
  ClearList(L); 
  printf("清空L后，L=");
  ListTraverse(L, print);
  i=ListEmpty(L); 
  printf("L是否空？i=%d（1：是 0：否），表L的长度=%d\n", i, ListLength(L));
  for(j=1; j<=10; j++)
    ListInsert(L, j, j); 
  printf("在L的表尾依次插入1～10后，L=");
  ListTraverse(L, print); 
  for(j=0; j<=1; j++)
  {
#ifdef SLL 
    k=LocateElem(L, j); 
    if(k) 
      printf("值为%d的元素的位序为%d\n", j, k);
#else 
    k=LocateElem(L, j, equal); 
    if(k) 
      printf("第%d个元素的值为%d\n", k, j);
#endif
    else 
      printf("没有值为%d的元素，", j);
  }
  for(j=1; j<=2; j++) 
  { GetElem(L, j, e0); 
    i=PriorElem(L, e0, e); 
    if(i==ERROR) 
      printf("元素%d无前驱，", e0);
    else 
      printf("元素%d的前驱为%d\n", e0, e);
  }
  for(j=ListLength(L)-1; j<=ListLength(L); j++) 
  { GetElem(L, j, e0); 
    i=NextElem(L, e0, e); 
    if(i==ERROR) 
      printf("元素%d无后继\n", e0);
    else 
      printf("元素%d的后继为%d，", e0, e);
  }
  k=ListLength(L); 
  for(j=k+1; j>=k; j--)
  { i=ListDelete(L, j, e); 
    if(i==ERROR) 
      printf("删除第%d个元素失败（不存在此元素）。", j);
    else 
      printf("删除第%d个元素成功，其值为%d\n", j, e);
  }
  printf("依次输出L的元素：");
  ListTraverse(L, print); 
  DestroyList(L); 
#ifndef SLL 
  printf("销毁L后，L=%u\n", L);
#endif
}


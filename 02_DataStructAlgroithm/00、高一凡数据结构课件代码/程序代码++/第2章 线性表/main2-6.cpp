// main2-6.cpp ����bo2-7.h��������
#include"c1.h"
typedef int ElemType; 
#include"c2-4.h" 
#include"bo2-7.h" 
#include"func2-2.h" 
void main()
{
  DuLinkList L;
  int i, n=4;
  Status j;
  ElemType e;
  InitList(L); 
  for(i=1; i<=5; i++) 
    ListInsert(L, i, i); 
  printf("�����������");
  ListTraverseBack(L, print); 
  j=GetElem(L, 2, e); 
  if(j)
    printf("����ĵ�2��Ԫ��ֵΪ%d\n", e);
  else
    printf("�����ڵ�2��Ԫ��\n");
  i=LocateElem(L, n, equal);
  if(i)
    printf("����%d��Ԫ���ǵ�%d��\n", n, i);
  else
    printf("û�е���%d��Ԫ��\n", n);
  j=PriorElem(L, n, e);
  if(j)
    printf("%d��ǰ����%d��", n, e);
  else
    printf("������%d��ǰ��\n", n);
  j=NextElem(L, n, e);
  if(j)
    printf("%d�ĺ����%d\n", n, e);
  else
    printf("������%d�ĺ��\n", n);
  ListDelete(L, 2, e); 
  printf("ɾ����2����㣬ֵΪ%d��������Ϊ ", e); 
  ListTraverse(L, print); 
  printf("�����Ԫ�ظ���Ϊ%d��", ListLength(L));
  printf("�����Ƿ�գ�%d��1���� 0����\n", ListEmpty(L));
  ClearList(L); 
  printf("��պ������Ƿ�գ�%d��1���� 0����\n", ListEmpty(L));
  DestroyList(L);
}


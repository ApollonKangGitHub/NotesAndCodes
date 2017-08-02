// main2-1.cpp ����bo2-1.h��������
#include"c1.h"
typedef int ElemType; 
#include"c2-1.h" 
#include"bo2-1.h" 
#include"func2-2.h" 
Status sq(ElemType c1, ElemType c2)
{ 
  if(c1==c2*c2)
    return TRUE;
  else
    return FALSE;
}
void dbl(ElemType &c)
{ 
  c*=2;
}
void main()
{
  SqList L;
  ElemType e, e0;
  Status i;
  int j, k;
  InitList(L); 
  printf("��ʼ��L��L.length=%d��L.listsize=%d��L.elem=%u\n",
  L.length, L.listsize, L.elem);
  for(j=1; j<=5; j++)
    i=ListInsert(L, 1, j); 
  printf("��L�ı�ͷ���β���1��5��*L.elem=");
  for(j=1; j<=5; j++)
    printf("%d ", *(L.elem+j-1)); 
  printf("\n����ListTraverse()���������������L�е�Ԫ�أ�");
  ListTraverse(L, print1); 
  i=ListEmpty(L); 
  printf("L.length=%d��L.listsize=%d�����䣩��", L.length, L.listsize);
  printf("L.elem=%u�����䣩��L�Ƿ�գ�i=%d\n", L.elem, i);
  ClearList(L); 
  i=ListEmpty(L); 
  printf("���L��L.length=%d��L.listsize=%d��", L.length, L.listsize);
  printf("L.elem=%u��L�Ƿ�գ�i=%d��1���� 0����\n", L.elem, i);
  for(j=1; j<=10; j++)
    ListInsert(L, j, j); 
  printf("��L�ı�β���β���1��10��L=");
  ListTraverse(L, print1); 
  printf("L.length=%d��L.listsize=%d��L.elem=%u\n",L.length,L.listsize,L.elem);
  ListInsert(L, 1, 0); 
  printf("��L�ı�ͷ����0��L.length=%d��L.listsize=%d���ı䣩��"
  "L.elem=%u�����ܸı䣩\n", L.length, L.listsize, L.elem);
  GetElem(L, 5, e); 
  printf("��5��Ԫ�ص�ֵΪ%d\n", e);
  for(j=10; j<=11; j++)
  { k=LocateElem(L, j, equal); 
    if(k) 
      printf("��%d��Ԫ�ص�ֵΪ%d��", k, j);
    else 
      printf("û��ֵΪ%d��Ԫ��\n", j);
  }
  for(j=3; j<=4; j++) 
  { k=LocateElem(L, j, sq); 
    if(k) 
      printf("��%d��Ԫ�ص�ֵΪ%d��ƽ����", k, j);
    else 
      printf("û��ֵΪ%d��ƽ����Ԫ��\n", j);
  }
  for(j=1; j<=2; j++) 
  { GetElem(L, j, e0); 
    i=PriorElem(L, e0, e); 
    if(i==ERROR) 
      printf("Ԫ��%d��ǰ����", e0);
    else 
      printf("Ԫ��%d��ǰ��Ϊ%d\n", e0, e);
  }
  for(j=ListLength(L)-1; j<=ListLength(L); j++) 
  { GetElem(L, j, e0); 
    i=NextElem(L, e0, e); 
    if(i==ERROR) 
      printf("Ԫ��%d�޺��\n", e0);
    else 
      printf("Ԫ��%d�ĺ��Ϊ%d��", e0, e);
  }
  k=ListLength(L); 
  for(j=k+1; j>=k; j--)
  { i=ListDelete(L, j, e); 
    if(i==ERROR) 
      printf("ɾ����%d��Ԫ��ʧ�ܡ�", j);
    else 
      printf("ɾ����%d��Ԫ�سɹ�����ֵΪ%d", j, e);
  }
  ListTraverse(L, dbl); 
  printf("L��Ԫ��ֵ�ӱ���L=");
  ListTraverse(L, print1); 
  DestroyList(L); 
  printf("����L��L.length=%d��L.listsize=%d��L.elem=%u\n",
  L.length, L.listsize, L.elem);
}


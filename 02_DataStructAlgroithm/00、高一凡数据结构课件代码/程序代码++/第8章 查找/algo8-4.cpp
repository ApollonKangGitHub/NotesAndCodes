// algo8-4.cpp ����bo8-2.h�ĳ���
#include"c1.h"
#include"func8-5.h" 
#include"c8-2.h" 
typedef ElemType TElemType; 
#include"c6-1.h" 
#include"func8-4.h" 
#include"bo8-2.h" 
void main()
{
  BiTree dt, p;
  int i, n;
  KeyType j;
  ElemType r;
  Status k;
  FILE *f; 
  f=fopen("f8-4.txt", "r"); 
  fscanf(f, "%d", &n); 
  InitDSTable(dt); 
  for(i=0; i<n; i++) 
  { InputFromFile(f, r); 
    k=InsertBST(dt, r); 
    if(!k) 
      printf("����������dt���Ѵ��ڹؼ���Ϊ%d�����ݣ���(%d,%d)�޷����뵽dt�С�\n", 
      r.key, r.key, r.others);
  }
  fclose(f); 
  printf("�����������������dt��\n");
  TraverseDSTable(dt, Visit); 
  printf("\n�����������������dt��\n");
  PreOrderTraverse(dt, Visit); 
  printf("\n����������ҵĹؼ��ֵ�ֵ��");
  InputKey(j); 
  p=SearchBST(dt, j); 
  if(p) 
  { printf("dt�д��ڹؼ���Ϊ%d�Ľ�㡣", j);
    DeleteBST(dt, j); 
    printf("ɾ���˽��������������������dt��\n");
    TraverseDSTable(dt, Visit); 
    printf("\n�����������������dt��\n");
    PreOrderTraverse(dt, Visit); 
    printf("\n");
  }
  else 
    printf("dt�в����ڹؼ���Ϊ%d�Ľ�㡣\n", j);
  DestroyDSTable(dt); 
}


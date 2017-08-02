// algo8-5.cpp ����bo8-3.h�ĳ���
#include"c1.h"
#include"func8-5.h" 
#include"c8-2.h" 
typedef ElemType TElemType; 
#include"c8-3.h" 
typedef BSTree BiTree; 
#include"func8-4.h" 
//#define FLAG // �Ӵ˾���bo8-3.h��ֱ����RL��LRƽ�⴦����9��
#include"bo8-3.h" 
void main()
{
  BSTree dt, p;
  int i, n;
  KeyType j;
  ElemType r;
  Boolean flag;
  Status k;
  FILE *f; 
  f=fopen("f8-4.txt", "r"); 
  fscanf(f, "%d", &n); 
  InitDSTable(dt); 
  for(i=0; i<n; i++) 
  { InputFromFile(f, r); 
    k=InsertAVL(dt, r, flag); 
    if(k) 
    { printf("����ؼ���Ϊ%d�Ľ��󣬰��ؼ���˳�����򣩱���ƽ�������dt\n", r.key);
      TraverseDSTable(dt, Visit); 
      printf("\n�������ƽ�������dt\n");
      PreOrderTraverse(dt, Visit); 
      printf("\n");
    }
    else 
      printf("ƽ�������dt���Ѵ��ڹؼ���Ϊ%d�����ݣ���(%d,%d)�޷����뵽dt�С�\n",
      r.key, r.key, r.others);
  }
  fclose(f); 
  printf("����������ҵĹؼ��ֵ�ֵ��");
  InputKey(j); 
  p=SearchBST(dt, j); 
  if(p) 
    printf("dt�д��ڹؼ���Ϊ%d�Ľ�㣬��ֵΪ(%d,%d)��\n", j, p->data.key, 
    p->data.others);
  else
    printf("dt�в����ڹؼ���Ϊ%d�Ľ�㡣\n", j);
  printf("�������ɾ���Ĺؼ��ֵ�ֵ��");
  InputKey(r.key); 
  k=DeleteAVL(dt, r, flag); 
  if(k) 
  { printf("ɾ�����(%d, %d)���������ƽ�������dt\n",r.key, r.others);
    TraverseDSTable(dt, Visit); 
    printf("\n�������ƽ�������dt\n");
    PreOrderTraverse(dt, Visit); 
    printf("\n");
  }
  else 
    printf("ƽ�������dt�в����ڹؼ���Ϊ%d�����ݡ�\n", r.key);
  DestroyDSTable(dt); 
}


// algo8-7.cpp ����bo8-5.h�ĳ���
#include"c1.h"
#define N 20 
struct Others 
{ int order; 
};
#define Nil '$' 
#include"c8-7.h" 
#include"c8-4.h" 
#include"c8-8.h" 
#include"bo8-5.h" 
#include"func8-7.h" 
void main()
{
  DLTree t;
  int i, j=0; 
  KeyType k;
  Status flag;
  Record *p, r[N]; 
  FILE *f; 
  InitDSTable(t); 
  f=fopen("f8-6.txt", "r"); 
  do 
  { i=fscanf(f, "%s%d", &r[j].key.ch, &r[j].others.order);
    if(i==2) 
    { r[j].key.num=strlen(r[j].key.ch); 
      flag=InsertDSTable(t, &r[j]); 
      if(flag==FALSE)
        printf("��t���Ѵ��ڹؼ���Ϊ%s�ļ�¼����(%s,%d)�޷����롣\n", 
      r[j].key.ch, r[j].key.ch, r[j].others.order);
	  else
        j++; 
    }
  }while(!feof(f) && j<N); 
  fclose(f); 
  printf("���ؼ��ַ�����˳�������t��\n");
  TraverseDSTable(t, Visit); 
  printf("\n����������Ҽ�¼�Ĺؼ��ַ�����");
  InputKey(k.ch); 
  k.num=strlen(k.ch); 
  p=SearchDLTree(t, k); 
  if(p) 
    Visit(p); 
  else 
    printf("δ�ҵ�"); 
  printf("\n");
  DestroyDSTable(t); 
}


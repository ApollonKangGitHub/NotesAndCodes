// algo8-8.cpp ����bo8-6.h�ĳ���
#include"c1.h"
#define N 20 
#define LENGTH 27 
struct Others 
{ int order; 
};
#define Nil 0 
static int count=0; 
#include"c8-7.h" 
#include"c8-4.h" 
#include"c8-9.h" 
#include"c8-10.h" 
int ord(char c)
{ if(c==Nil)
    return 0; 
  else
    return toupper(c)-'A'+1; 
}
#include"bo8-6.h" 
#include"func8-7.h" 
void main()
{
  TrieTree t;
  int i, j=0; 
  KeyType k;
  Record *p, r[N]; 
  FILE *f; 
  InitDSTable(t); 
  f=fopen("f8-6.txt", "r"); 
  do 
  { i=fscanf(f, "%s%d", &r[j].key.ch, &r[j].others.order); 
    if(i==2) 
    { r[j].key.num=strlen(r[j].key.ch); 
      p=SearchTrie(t, r[j].key); 
      if(!p) 
        InsertTrie(t, &r[j++]);
        
      else 
        printf("��t���Ѵ��ڹؼ���Ϊ%s�ļ�¼����(%s,%d)�޷����롣\n", 
        r[j].key.ch, r[j].key.ch, r[j].others.order);
    }
  }while(!feof(f) && j<N); 
  fclose(f); 
  printf("���ؼ��ַ�����˳�������t��\n");
  TraverseDSTable(t, Visit); 
  printf("\n����������Ҽ�¼�Ĺؼ��ַ�����");
  InputKey(k.ch); 
  k.num=strlen(k.ch); 
  p=SearchTrie(t, k); 
  if(p) 
    Visit(p); 
  else 
    printf("δ�ҵ�"); 
  printf("\n");
  DestroyDSTable(t); 
}


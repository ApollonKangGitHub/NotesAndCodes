// algo8-9.cpp ����bo8-7.h�ĳ���
#include"c1.h"
#define NULL_KEY 0 
#define N 15 
int m; 
typedef int KeyType; 
struct ElemType 
{ KeyType key;
  int order;
};
#include"c8-2.h"
#include"c8-11.h"
#include"bo8-7.h"
void Visit(int p, ElemType r)
{ printf("address=%d (%d, %d)\n", p, r.key, r.order);
}
void main()
{
  ElemType r[N]; 
  HashTable h;
  int i, n, p=0;
  Status j;
  KeyType k;
  FILE *f; 
  f=fopen("f8-7.txt", "r"); 
  do 
  { i=fscanf(f, "%d%d", &r[p].key, &r[p].order); 
    if(i==2) 
      p++;
  }while(!feof(f) && p<N); 
  fclose(f); 
  InitHashTable(h); 
  for(i=0; i<p-1; i++)
  { j=InsertHash(h, r[i]); 
    if(j==DUPLICATE)
      printf("�������йؼ���Ϊ%d�ļ�¼���޷��ٲ����¼(%d, %d)\n", 
      r[i].key, r[i].key, r[i].order);
  }
  printf("����ϣ��ַ��˳�������ϣ��\n");
  TraverseHash(h, Visit); 
  printf("����������Ҽ�¼�Ĺؼ��֣�");
  scanf("%d", &k); 
  j=SearchHash(h, k, p, n); 
  if(j==SUCCESS) 
    Visit(p, h.elem[p]); 
  else 
    printf("δ�ҵ�\n"); 
  j=InsertHash(h, r[i]); 
  if(j==ERROR) 
    j=InsertHash(h, r[i]); 
  printf("����ϣ��ַ��˳������ؽ���Ĺ�ϣ��\n");
  TraverseHash(h, Visit); 
  printf("����������Ҽ�¼�Ĺؼ��֣�");
  scanf("%d", &k); 
  j=SearchHash(h, k, p, n); 
  if(j==SUCCESS) 
    Visit(p, h.elem[p]); 
  else 
    printf("δ�ҵ�\n"); 
  DestroyHashTable(h); 
}


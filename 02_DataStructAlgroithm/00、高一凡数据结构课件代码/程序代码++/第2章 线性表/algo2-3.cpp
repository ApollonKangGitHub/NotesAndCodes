// algo2-3.cpp ʵ���㷨2.11��2.12�ĳ���
#include"c1.h"
typedef int ElemType; 
#include"c2-2.h" 
#include"bo2-2.h" 
#include"func2-2.h" 
void CreateList(LinkList &L, int n) 
{ 
  int i;
  LinkList p;
  L=(LinkList)malloc(sizeof(LNode)); 
  L->next=NULL; 
  printf("������%d������\n", n);
  for(i=n; i>0; --i)
  { p=(LinkList)malloc(sizeof(LNode)); 
    scanf("%d", &p->data); 
    p->next=L->next; 
    L->next=p; 
  }
}
void CreateList1(LinkList &L, int n)
{ 
  int i;
  LinkList p, q;
  L=(LinkList)malloc(sizeof(LNode)); 
  L->next=NULL; 
  q=L; 
  printf("������%d������\n", n);
  for(i=1; i<=n; i++)
  { p=(LinkList)malloc(sizeof(LNode)); 
    scanf("%d", &p->data); 
    q->next=p; 
    q=q->next; 
  }
  p->next=NULL; 
}
void MergeList(LinkList La, LinkList &Lb, LinkList &Lc) 
{ 
  
  LinkList pa=La->next,pb=Lb->next,pc;
  Lc=pc=La; 
  while(pa && pb) 
    if(pa->data<=pb->data) 
    { pc->next=pa; 
      pc=pa; 
      pa=pa->next; 
    }
    else 
    { pc->next=pb; 
      pc=pb; 
      pb=pb->next; 
    }
  pc->next=pa ? pa : pb; 
  free(Lb); 
  Lb=NULL; 
}
void main()
{
  int n=5;
  LinkList La, Lb, Lc;
  printf("���ǵݼ�˳��");
  CreateList1(La, n); 
  printf("La="); 
  ListTraverse(La, print); 
  printf("���ǵ���˳��");
  CreateList(Lb, n); 
  printf("Lb="); 
  ListTraverse(Lb, print); 
  MergeList(La, Lb, Lc); 
  printf("Lc="); 
  ListTraverse(Lc, print); 
}


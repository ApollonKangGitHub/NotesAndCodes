// algo11-2.cpp 伙伴系统。实现算法8.2的程序
#include"c1.h"
#include"c11-2.h" 
#define N 100 
Space r; 
Space AllocBuddy(FreeList &avail, int n)
{ 
  
  int i, k;
  Space pa, pi, pre, suc;
  for(k=0; k<=m && (avail[k].nodesize<n+1 || !avail[k].first); k++);
  
  if(k>m) 
    return NULL;
  else 
  { pa=avail[k].first; 
    pre=pa->llink; 
    suc=pa->rlink;
    if(pa==suc)
      avail[k].first=NULL; 
    else 
    { pre->rlink=suc;
      suc->llink=pre;
      avail[k].first=suc;
    }
    for(i=1; avail[k-i].nodesize>=n+1; i++)
    { pi=pa+int(pow(2, k-i));
      pi->rlink=pi;
      pi->llink=pi;
      pi->tag=0;
      pi->kval=k-i;
      avail[k-i].first=pi;
    } 
    pa->tag=1;
    pa->kval=k-(--i);
  }
  return pa;
}
Space buddy(Space p)
{ 
  if((p-r)%int(pow(2, p->kval+1))==0) 
    return p+int(pow(2, p->kval));
  else 
    return p-int(pow(2, p->kval));
}
void Reclaim(FreeList &pav, Space &p)
{ 
  Space s;
  s=buddy(p); 
  while(s>=r && s<r+pav[m].nodesize && s->tag==0)
  
  { 
    if(s->llink==s && s->rlink==s) 
      pav[s->kval].first=NULL; 
    else 
    { s->llink->rlink=s->rlink; 
      s->rlink->llink=s->llink; 
      if(pav[s->kval].first==s) 
        pav[s->kval].first=s->rlink; 
    } 
    if((p-r)%int(pow(2, p->kval+1))==0) 
      p->kval++;
    else 
    { s->kval=p->kval+1;
      p=s; 
    }
    s=buddy(p); 
  } 
  p->tag=0;
  if(pav[p->kval].first==NULL) 
    pav[p->kval].first=p->llink=p->rlink=p;
  else 
  { p->rlink=pav[p->kval].first;
    p->llink=p->rlink->llink;
    p->rlink->llink=p;
    p->llink->rlink=p;
    pav[p->kval].first=p;
  }
  p=NULL;
}
void Print(FreeList p)
{ 
  Space h;
  for(int i=0; i<=m; i++)
  { if(p[i].first) 
    { h=p[i].first; 
      do
      { printf("块的大小=%d 块的首地址=%u ", int(pow(2, h->kval)), h);
        
        printf("块标志=%d（0：空闲 1：占用）\n", h->tag);
        h=h->rlink; 
      }while(h!=p[i].first); 
    }
  }
}
void PrintUser(Space p[])
{ 
  for(int i=0; i<N; i++)
    if(p[i]) 
    { printf("占用块%d的首地址=%u ", i, p[i]); 
      printf("块的大小=%d", int(pow(2, p[i]->kval)));
      printf(" 块标志=%d（0：空闲 1：占用）\n", p[i]->tag);
    }
}
void main()
{
  int i, n;
  FreeList a;
  Space q[N]={NULL}; 
  printf("sizeof(WORD)=%u m=%u int(pow(2, m))=%u\n",
  sizeof(WORD), m, int(pow(2, m)));
  for(i=0; i<=m; i++) 
  { a[i].nodesize=int(pow(2, i));
    a[i].first=NULL;
  }
  r=a[m].first=(Space)malloc(a[m].nodesize*sizeof(WORD));
  
  if(r) 
  { r->llink=r->rlink=r; 
    r->tag=0;
    r->kval=m;
    Print(a);
    PrintUser(q);
    n=100;
    q[0]=AllocBuddy(a, n);
  
    printf("申请%d个字后，可利用空间为\n", n);
    Print(a);
    PrintUser(q);
    n=200;
    q[1]=AllocBuddy(a, n);
  
    printf("申请%d个字后，可利用空间为\n", n);
    Print(a);
    PrintUser(q);
    n=220;
    q[2]=AllocBuddy(a, n);
  
    printf("申请%d个字后，可利用空间为\n", n);
    Print(a);
    PrintUser(q);
    Reclaim(a, q[1]); 
    printf("回收q[1]后，可利用空间为\n");
    Print(a);
    PrintUser(q);
    Reclaim(a, q[0]); 
    printf("回收q[0]后，可利用空间为\n");
    Print(a);
    PrintUser(q);
    Reclaim(a, q[2]); 
    printf("回收q[2]后，可利用空间为\n");
    Print(a);
    PrintUser(q);
    free(r); 
 }
  else
    printf("ERROR\n");
}


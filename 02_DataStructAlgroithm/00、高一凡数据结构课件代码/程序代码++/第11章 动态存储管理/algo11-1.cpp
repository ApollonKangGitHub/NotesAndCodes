// algo11-1.cpp �߽��ʶ����ʵ���㷨8.1�ĳ���
#include"c1.h"
#include"c11-1.h" 
#define MAX 1000 
#define e 10 
Space AllocBoundTag(Space &pav, int n) 
{ 
  
  Space p, f;
  for(p=pav; p && p->size<n && p->rlink!=pav; p=p->rlink); 
  if(!p || p->size<n) 
    return NULL;
  else 
  { f=FootLoc(p); 
    pav=p->rlink; 
    if(p->size-n<=e) 
    { if(pav==p) 
        pav=NULL;
      else 
      { pav->llink=p->llink;
        p->llink->rlink=pav;
      }
      p->tag=f->tag=1; 
    }
    else 
    { f->tag=1; 
      p->size-=n; 
      f=FootLoc(p); 
      f->tag=0; 
      f->uplink=p;
      p=f+1; 
      p->tag=1; 
      p->size=n;
    }
    return p; 
  }
}
void Reclaim(Space &pav, Space &p)
{ 
  Space s=(p-1)->uplink, t=p+p->size;
  
  int l=(p-1)->tag, r=(p+p->size)->tag; 
  if(!pav) 
  { 
    pav=p->llink=p->rlink=p; 
    p->tag=0; 
    (FootLoc(p))->uplink=p; 
    (FootLoc(p))->tag=0;
  }
  else 
  { if(l==1 && r==1) 
    { p->tag=0; 
      (FootLoc(p))->uplink=p; 
      (FootLoc(p))->tag=0;
      pav->llink->rlink=p; 
      p->llink=pav->llink;
      p->rlink=pav;
      pav->llink=p;
      pav=p; 
    }
    else if(l==0 && r==1) 
    { 
      s=(p-1)->uplink; 
      s->size+=p->size; 
      t=FootLoc(p); 
      t->uplink=s; 
      t->tag=0; 
    }
    else if(l==1 && r==0) 
    { 
      p->tag=0; 
      p->llink=t->llink; 
      p->llink->rlink=p; 
      p->rlink=t->rlink; 
      p->rlink->llink=p; 
      p->size+=t->size; 
      (FootLoc(t))->uplink=p; 
      if(pav==t) 
        pav=p; 
    }
    else 
    { 
      s->size+=p->size+t->size; 
      t->llink->rlink=t->rlink; 
      t->rlink->llink=t->llink;
      (FootLoc(t))->uplink=s; 
      if(pav==t) 
        pav=s; 
    }
  }
  p=NULL; 
}
void Print(Space p)
{ 
  Space h, f;
  if(p) 
  { h=p; 
    f=FootLoc(h); 
    do
    { printf("��Ĵ�С=%d ����׵�ַ=%u ", h->size, f->uplink); 
      printf("���־=%d��0������ 1��ռ�ã��ڿ��׵�ַ=%u\n", h->tag, f+1);
      h=h->rlink; 
      f=FootLoc(h); 
    }while(h!=p); 
  }
}
void PrintUser(Space p[])
{ 
  for(int i=0; i<MAX/e; i++)
    if(p[i]) 
    { printf("��%d���׵�ַ=%u ", i, p[i]); 
      printf("��Ĵ�С=%d ��ͷ��־=%d��0������ 1��ռ�ã�", p[i]->size, p[i]->tag);
      printf(" ��β��־=%d\n", (FootLoc(p[i]))->tag);
    }
}
void main()
{
  Space pav, p; 
  Space v[MAX/e]={NULL}; 
  int n;
  printf("�ṹ��WORDΪ%d���ֽ�\n", sizeof(WORD));
  p=(Space)malloc((MAX+2)*sizeof(WORD));
  
  p->tag=1; 
  pav=p+1; 
  pav->rlink=pav->llink=pav; 
  pav->tag=0;
  pav->size=MAX;
  p=FootLoc(pav); 
  p->uplink=pav;
  p->tag=0;
  (p+1)->tag=1; 
  printf("��ʼ���󣬿����ÿռ��Ϊ \n");
  Print(pav);
  n=300;
  v[0]=AllocBoundTag(pav, n);
  printf("����%u���洢�ռ�󣬿����ÿռ��Ϊ \n", n);
  Print(pav);
  PrintUser(v);
  n=450;
  v[1]=AllocBoundTag(pav, n);
  printf("����%u���洢�ռ��pavΪ \n", n);
  Print(pav);
  PrintUser(v);
  n=300; 
  v[2]=AllocBoundTag(pav, n);
  printf("����%u���洢�ռ�󣨲��ɹ�����pavΪ \n", n);
  Print(pav);
  PrintUser(v);
  n=242; 
  v[2]=AllocBoundTag(pav, n);
  printf("����%u���洢�ռ��������䣩��pavΪ \n", n);
  Print(pav);
  PrintUser(v);
  printf("����v[0]��%d���󣨵�pav��ʱ���գ���pavΪ \n", v[0]->size);
  Reclaim(pav, v[0]); 
  Print(pav);
  PrintUser(v);
  printf("1���س�������");
  getchar();
  printf("����v[2]��%d��������������Ϊռ�ÿ飩, pavΪ \n", v[2]->size);
  Reclaim(pav, v[2]); 
  Print(pav);
  PrintUser(v);
  n=270; 
  v[0]=AllocBoundTag(pav, n);
  printf("����%u���洢�ռ�󣨲��ҿռ��㹻��Ŀ飩��pavΪ \n", n);
  Print(pav);
  PrintUser(v);
  n=30; 
  v[2]=AllocBoundTag(pav, n);
  printf("����%u���洢�ռ���ڵ�ǰ���Ϸ��䣩��pavΪ \n", n);
  Print(pav);
  PrintUser(v);
  printf("����v[1]��%d����������Ϊ���п飬������Ϊռ�ÿ飩��pavΪ \n", v[1]->size);
  Reclaim(pav, v[1]); 
  Print(pav);
  PrintUser(v);
  printf("2���س�������");
  getchar();
  printf("����v[0]��%d����������Ϊ���п飬������Ϊռ�ÿ飩��pavΪ \n", v[0]->size);
  Reclaim(pav, v[0]); 
  Print(pav);
  PrintUser(v);
  printf("����v[2]��%d��������������Ϊ���п飩��pavΪ \n", v[2]->size);
  Reclaim(pav, v[2]); 
  Print(pav);
  PrintUser(v);
  pav=pav-1; 
  free(pav); 
}


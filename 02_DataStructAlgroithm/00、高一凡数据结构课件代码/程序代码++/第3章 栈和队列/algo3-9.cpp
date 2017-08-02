// algo3-9.cpp ����ҵ��ģ�⡣ʵ���㷨3.6��3.7�ĳ���
#define Qu 4 
#define Khjg 5 
#define Blsj 30 
typedef struct 
{ int OccurTime; 
  int NType; 
}Event, ElemType; 
struct LNode 
{ ElemType data;
  LNode *next;
};
struct LinkList 
{ LNode *head, *tail; 
  int len; 
};
#include"c1.h"
#include"OrderList.h" 
struct QElemType
{ int ArrivalTime; 
  int Duration; 
}; 
#include"c3-2.h" 
#include"bo3-2.h" 
// �������õ�����Ҫ������ȫ�֣�
typedef LinkList EventList; 
EventList ev; 
Event en, et; 
//FILE *fp; // �ļ���ָ�룬����ָ��b.txt��d.txt�ļ�
int TotalTime=0; 
int CloseTime, CustomerNum=0; 
int cmp(Event a, Event b)
{ 
  if(a.OccurTime==b.OccurTime)
    return 0;
  else
    return (a.OccurTime-b.OccurTime)/abs(a.OccurTime-b.OccurTime);
}
void Random(int &d, int &i)
{ 
  d=rand()%Blsj+1; 
  i=rand()%(Khjg+1); 
}
LinkQueue q[Qu]; 
QElemType customer; 
//FILE *fq; // �ļ���ָ�룬����ָ��a.txt�ļ�
void OpenForDay()
{ 
  InitList(ev); 
  en.OccurTime=0; 
//fprintf(fq,"��λ�ͻ�����ʱ��=%3d,",en.OccurTime);
  en.NType=Qu; 
  OrderInsert(ev, en, cmp); 
  for(int i=0; i<Qu; i++)
    InitQueue(q[i]); 
}
int Minimum(LinkQueue Q[])
{ 
  int l[Qu];
  int i, k=0;
  for(i=0; i<Qu; i++)
    l[i]=QueueLength(Q[i]);
  for(i=1; i<Qu; i++)
    if(l[i]<l[0])
    { l[0]=l[i];
      k=i;
    }
  return k;
}
void CustomerArrived()
{ 
  QElemType f;
  int durtime, intertime, i;
  ++CustomerNum; 
  Random(durtime, intertime);
  
  et.OccurTime=en.OccurTime+intertime;
  
  et.NType=Qu; 
  i=Minimum(q); 
//if(CustomerNum<=20) // ���ǰ20���ͻ�������Ϣ���ļ�a.txt��
//  fprintf(fq,"����ҵ���ʱ��=%2d,���Ŷ���=%d\n��һ�ͻ�����ʱ��=%3d,", durtime, i,
//    et.OccurTime);
  if(et.OccurTime<CloseTime) 
    OrderInsert(ev, et, cmp); 
  f.ArrivalTime=en.OccurTime; 
  f.Duration=durtime;
  EnQueue(q[i], f); 
  if(QueueLength(q[i])==1) 
  { et.OccurTime=en.OccurTime+durtime; 
    et.NType=i;
    OrderInsert(ev, et, cmp); 
  }
}
void CustomerDeparture()
{ 
  int i=en.NType; 
  DeQueue(q[i], customer); 
  TotalTime+=en.OccurTime-customer.ArrivalTime;
  
  if(!QueueEmpty(q[i]))
  { 
    GetHead(q[i], customer); 
    et.OccurTime=en.OccurTime+customer.Duration;
    
    et.NType=i; 
    OrderInsert(ev, et, cmp); 
  }
}
void Bank_Simulation()
{ 
  LNode *p;
  OpenForDay(); 
  while(!ListEmpty(ev)) 
  { DelFirst(ev, ev.head, p); 
//  if(p->data.OccurTime<50) // ���ǰ50�����ڷ������¼����ļ�d.txt��
//   fprintf(fp,"p->data.OccurTime=%3d p->data.NType=%d\n",p->data.OccurTime,p->data.NType);
    en.OccurTime=GetCurElem(p).OccurTime; 
    en.NType=GetCurElem(p).NType;
    if(en.NType==Qu) 
      CustomerArrived(); 
    else 
      CustomerDeparture(); 
  } 
  printf("������=%d �����ڵ���Ŀͻ���ʱ����=0��%d���� ÿ���ͻ�����ҵ���ʱ��="
  "1��%d����\n", Qu, Khjg, Blsj);
  printf("�ͻ�����:%d,���пͻ�����ʱ:%ld����,ƽ��ÿ�˺�ʱ:%d����,", CustomerNum, TotalTime, TotalTime/CustomerNum);
  printf("���һ���ͻ��뿪ʱ��:%d��\n", en.OccurTime);
}
void main()
{
//fq=fopen("a.txt","w"); // ��a.txt�ļ�������д��ͻ�������Ϣ
//fp=fopen("b.txt","w"); // ��b.txt�ļ�������д�������¼������ʷ��¼
  printf("����������Ӫҵʱ�䳤��(��λ����)��");
  scanf("%d", &CloseTime);
//srand(time(0)); // ��5��
  
  Bank_Simulation();
//fclose(fq); // �ر�a.txt
//fclose(fp); // �ر�b.txt
}


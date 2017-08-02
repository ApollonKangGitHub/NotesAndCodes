// algo3-9.cpp 银行业务模拟。实现算法3.6、3.7的程序
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
// 程序中用到的主要变量（全局）
typedef LinkList EventList; 
EventList ev; 
Event en, et; 
//FILE *fp; // 文件型指针，用于指向b.txt或d.txt文件
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
//FILE *fq; // 文件型指针，用于指向a.txt文件
void OpenForDay()
{ 
  InitList(ev); 
  en.OccurTime=0; 
//fprintf(fq,"首位客户到达时刻=%3d,",en.OccurTime);
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
//if(CustomerNum<=20) // 输出前20个客户到达信息到文件a.txt中
//  fprintf(fq,"办理业务的时间=%2d,所排队列=%d\n下一客户到达时刻=%3d,", durtime, i,
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
//  if(p->data.OccurTime<50) // 输出前50分钟内发生的事件到文件d.txt中
//   fprintf(fp,"p->data.OccurTime=%3d p->data.NType=%d\n",p->data.OccurTime,p->data.NType);
    en.OccurTime=GetCurElem(p).OccurTime; 
    en.NType=GetCurElem(p).NType;
    if(en.NType==Qu) 
      CustomerArrived(); 
    else 
      CustomerDeparture(); 
  } 
  printf("窗口数=%d 两相邻到达的客户的时间间隔=0～%d分钟 每个客户办理业务的时间="
  "1～%d分钟\n", Qu, Khjg, Blsj);
  printf("客户总数:%d,所有客户共耗时:%ld分钟,平均每人耗时:%d分钟,", CustomerNum, TotalTime, TotalTime/CustomerNum);
  printf("最后一个客户离开时间:%d分\n", en.OccurTime);
}
void main()
{
//fq=fopen("a.txt","w"); // 打开a.txt文件，用于写入客户到达信息
//fp=fopen("b.txt","w"); // 打开b.txt文件，用于写入有序事件表的历史记录
  printf("请输入银行营业时间长度(单位：分)：");
  scanf("%d", &CloseTime);
//srand(time(0)); // 第5行
  
  Bank_Simulation();
//fclose(fq); // 关闭a.txt
//fclose(fp); // 关闭b.txt
}


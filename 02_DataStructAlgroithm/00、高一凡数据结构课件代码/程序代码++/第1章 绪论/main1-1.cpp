// main1-1.cpp 检验基本操作bo1-1.h的主函数
#include"c1.h" 
// 以下两行可根据需要选其一（且只能选其一），而无须改变基本操作bo1-1.h
typedef int ElemType; 
//typedef double ElemType; // 定义抽象数据类型ElemType在本程序中为双精度型。第5行
#include"c1-1.h" 
#include"bo1-1.h" 
#include"func1-1.h" 
void main()
{
  Triplet T;
  ElemType m;
  Status i;
  i=InitTriplet(T, 5, 7, 9); 
//i=InitTriplet(T, 5.0, 7.1, 9.3); // 当ElemType为双精度型时，可取代上句。第15行
  printf("调用初始化函数后，i=%d（1：成功）。T的3个值为",i);
  PrintT(T); 
  i=Get(T, 2, m); 
  if(i==OK) 
  { printf("T的第2个值为");
    PrintE(m); 
  }
  i=Put(T, 2, 6); 
  if(i==OK) 
  { printf("将T的第2个值改为6后，T的3个值为");
    PrintT(T); 
  }
  i=IsAscending(T); 
  printf("调用测试升序的函数后，i=%d（0：否 1：是）\n", i);
  i=IsDescending(T); 
  printf("调用测试降序的函数后，i=%d（0：否 1：是）\n", i);
  if((i=Max(T, m))==OK) 
  { printf("T中的最大值为");
    PrintE(m); 
  }
  if((i=Min(T, m))==OK)
  { printf("T中的最小值为");
    PrintE(m); 
  }
  DestroyTriplet(T); 
  printf("销毁T后，T=%u\n", T);
}


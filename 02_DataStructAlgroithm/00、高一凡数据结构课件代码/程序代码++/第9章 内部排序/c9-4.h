// c9-4.h ����������������͡��������286ҳ�����޸�
#define MAX_NUM_OF_KEY 8 
#define RADIX 6 
#define MAX_SPACE 100
struct SLCell 
{ char keys[MAX_NUM_OF_KEY]; 
  char otheritems[15]; 
  int next;
};
struct SqList 
{ SLCell r[MAX_SPACE]; 
  int keynum; 
  int length; 
};
typedef int ArrType[RADIX]; 


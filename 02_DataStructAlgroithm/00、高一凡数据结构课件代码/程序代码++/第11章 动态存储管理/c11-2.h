// c11-2.h ���ϵͳ�����ÿռ��Ľṹ
#define m 10 
typedef struct WORD
{ WORD *llink; 
  int tag; 
  int kval; 
  WORD *rlink; 
}WORD, head, *Space; 
typedef struct HeadNode
{ int nodesize; 
  WORD *first; 
}FreeList[m+1]; 


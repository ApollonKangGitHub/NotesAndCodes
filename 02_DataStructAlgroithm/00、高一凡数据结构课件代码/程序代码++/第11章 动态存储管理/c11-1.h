// c11-1.h 边界标识法可利用空间表的结点结构
// head和foot分别是可利用空间表中结点的第一个字和最后一个字（WORD）
typedef struct WORD 
{ union
  { WORD *llink; 
    WORD *uplink; 
  };
  int tag; 
  int size; 
  WORD *rlink; 
}WORD, head, foot, *Space; 
#define FootLoc(p) p+p->size-1 


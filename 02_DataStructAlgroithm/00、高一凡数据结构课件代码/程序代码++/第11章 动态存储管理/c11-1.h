// c11-1.h �߽��ʶ�������ÿռ��Ľ��ṹ
// head��foot�ֱ��ǿ����ÿռ���н��ĵ�һ���ֺ����һ���֣�WORD��
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


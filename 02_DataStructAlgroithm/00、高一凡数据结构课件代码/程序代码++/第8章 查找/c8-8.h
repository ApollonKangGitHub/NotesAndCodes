// c8-8.h ˫�������Ĵ洢�ṹ���������248ҳ
typedef struct DLTNode 
{ char symbol; 
  DLTNode *next; 
  NodeKind kind; 
  union 
  { Record *infoptr; 
    DLTNode *first; 
  };
}DLTNode, *DLTree;


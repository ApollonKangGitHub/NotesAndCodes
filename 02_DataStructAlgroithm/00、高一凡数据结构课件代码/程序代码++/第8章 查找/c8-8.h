// c8-8.h 双链键树的存储结构。在严书第248页
typedef struct DLTNode 
{ char symbol; 
  DLTNode *next; 
  NodeKind kind; 
  union 
  { Record *infoptr; 
    DLTNode *first; 
  };
}DLTNode, *DLTree;


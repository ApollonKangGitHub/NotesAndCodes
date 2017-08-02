// c6-2.h 树的二叉链表（孩子—兄弟）存储结构。在严书第136页
typedef struct CSNode 
{ TElemType data; 
  CSNode *firstchild, *nextsibling;
}CSNode, *CSTree;


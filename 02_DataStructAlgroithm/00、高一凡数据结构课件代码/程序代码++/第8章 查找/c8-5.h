// c8-5.h B_树的结点类型。在严书第239页
typedef struct BTNode
{ int keynum; 
  BTNode *parent; 
  KeyType key[m+1]; 
  Record *recptr[m+1]; 
  BTNode *ptr[m+1]; 
}BTNode, *BTree; 


// c8-5.h B_���Ľ�����͡��������239ҳ
typedef struct BTNode
{ int keynum; 
  BTNode *parent; 
  KeyType key[m+1]; 
  Record *recptr[m+1]; 
  BTNode *ptr[m+1]; 
}BTNode, *BTree; 


// func8-4.h �����㷨9.5(a)��bo6-1.h��algo8-4.cpp��algo8-5.cpp����
#include"bo6-1.h" 
#define InitDSTable InitBiTree 
#define DestroyDSTable DestroyBiTree
#define TraverseDSTable InOrderTraverse
// ���ؼ���˳�����������������ƽ�����������������������Ĳ���ͬ
BiTree SearchBST(BiTree T, KeyType key)
{ 
  
  if(!T || EQ(key, T->data.key)) 
    return T; 
  else if LT(key, T->data.key) 
    return SearchBST(T->lchild, key); 
  else 
    return SearchBST(T->rchild, key); 
}


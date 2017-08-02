// main6-1.cpp 检验二叉链表基本操作的主程序
#define CHAR 1 
//#define CHAR 0 // 整型（二者选一）。第3行
#include"func6-1.h" 
#include"c6-1.h" 
#include"bo6-1.h" 
#include"bo6-2.h" 
void main()
{
  int i;
  BiTree T, p, c;
  TElemType e1, e2;
  InitBiTree(T); 
  printf("构造空二叉树后，树空否？%d（1：是 0：否）。树的深度=%d。\n", 
  BiTreeEmpty(T), BiTreeDepth(T));
  e1=Root(T); 
  if(e1!=Nil)
    printf("二叉树的根为"form"。\n", e1);
  else
    printf("树空，无根。\n");
#if CHAR 
  printf("请按先序输入二叉树（如：ab###表示a为根结点，b为左子树的二叉树）：\n");
#else 
  printf("请按先序输入二叉树（如：1 2 0 0 0表示1为根结点，2为左子树的二叉树）：\n");
#endif
  CreateBiTree(T); 
  printf("建立二叉树后，树空否？%d（1：是 0：否）。树的深度=%d。\n", BiTreeEmpty(T), 
  BiTreeDepth(T));
  e1=Root(T); 
  if(e1!=Nil)
    printf("二叉树的根为"form"。\n", e1);
  else
    printf("树空，无根。\n");
  printf("中序递归遍历二叉树：\n");
  InOrderTraverse(T, visit); 
  printf("\n后序递归遍历二叉树：\n");
  PostOrderTraverse(T, visit); 
  printf("\n请输入一个结点的值：");
  scanf("%*c"form, &e1);
  p=Point(T, e1); 
  printf("结点的值为"form"。\n", Value(p));
  printf("欲改变此结点的值，请输入新值：");
  scanf("%*c"form"%*c", &e2); 
  Assign(p, e2); 
  printf("层序遍历二叉树：\n");
  LevelOrderTraverse(T, visit); 
  e1=Parent(T, e2); 
  if(e1!=Nil)
    printf(form"的双亲是"form"，", e2, e1);
  else
    printf(form"没有双亲，", e2);
  e1=LeftChild(T, e2); 
  if(e1!=Nil)
    printf("左孩子是"form"，", e1);
  else
    printf("没有左孩子，");
  e1=RightChild(T, e2); 
  if(e1!=Nil)
    printf("右孩子是"form"，", e1);
  else
    printf("没有右孩子，");
  e1=LeftSibling(T, e2); 
  if(e1!=Nil)
    printf("左兄弟是"form"，", e1);
else
    printf("没有左兄弟，");
  e1=RightSibling(T, e2); 
  if(e1!=Nil)
    printf("右兄弟是"form"。\n", e1);
  else
    printf("没有右兄弟。\n");
  InitBiTree(c); 
  printf("请构造一个右子树为空的二叉树c：\n");
#if CHAR 
  printf("请按先序输入二叉树（如：ab###表示a为根结点，b为左子树的二叉树）：\n");
#else 
  printf("请按先序输入二叉树（如：1 2 0 0 0表示1为根结点，2为左子树的二叉树）：\n");
#endif
  CreateBiTree(c); 
  printf("中序递归遍历二叉树c：\n");
  InOrderTraverse(c, visit); 
  printf("\n树c插到树T中，请输入树T中树c的双亲结点 c为左（0）或右（1）子树：");
  scanf("%*c"form"%d", &e1, &i);
  p=Point(T, e1); 
  InsertChild(p, i, c);
  
  printf("先序递归遍历二叉树：\n");
  PreOrderTraverse(T, visit); 
  printf("\n删除子树，请输入待删除子树的双亲结点 左（0）或右（1）子树：");
  scanf("%*c"form"%d", &e1, &i);
  p=Point(T, e1); 
  DeleteChild(p, i); 
  printf("先序递归遍历二叉树：\n");
  PreOrderTraverse(T, visit); 
  printf("\n中序非递归遍历二叉树：\n");
  InOrderTraverse1(T, visit); 
  printf("中序非递归遍历二叉树（另一种方法）：\n");
  InOrderTraverse2(T, visit); 
  DestroyBiTree(T); 
}


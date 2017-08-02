// main6-2.cpp 检验bo6-3.h和bo6-4.h的程序
#define CHAR 1 
#include"func6-1.h" 
#include"c6-2.h" 
#include"bo6-3.h" 
#include"bo6-4.h" 
void main()
{
  int i;
  CSTree T, p, q;
  TElemType e, e1;
  InitTree(T); 
  printf("构造空树后，树空否？%d（1：是 0：否）。树根为%c，树的深度为%d。\n", 
  TreeEmpty(T), Root(T), TreeDepth(T));
  CreateTree(T); 
  printf("构造树T后，树空否？%d（1：是 0：否）。树根为%c，树的深度为%d。\n", 
  TreeEmpty(T), Root(T), TreeDepth(T));
  printf("层序遍历树T：\n");
  LevelOrderTraverse(T, visit); 
  printf("请输入待修改的结点的值 新值：");
  scanf("%c%*c%c%*c", &e, &e1);
  Assign(T, e, e1); 
  printf("层序遍历修改后的树T：\n");
  LevelOrderTraverse(T, visit); 
  printf("%c的双亲是%c，长子是%c，下一个兄弟是%c。\n", e1, Parent(T, e1), 
  LeftChild(T, e1), RightSibling(T, e1));
  printf("建立树p：\n");
  CreateTree(p); 
  printf("层序遍历树p：\n");
  LevelOrderTraverse(p, visit); 
  printf("将树p插到树T中，请输入T中p的双亲结点 子树序号：");
  scanf("%c%d%*c", &e, &i);
  q=Point(T, e); 
  InsertChild(T, q, i, p); 
  printf("层序遍历修改后的树T：\n");
  LevelOrderTraverse(T, visit); 
  printf("先根遍历树T：\n");
  PreOrderTraverse(T, visit); 
  printf("\n后根遍历树T：\n");
  PostOrderTraverse(T, visit); 
  printf("\n删除树T中结点e的第i棵子树，请输入e i：");
  scanf("%c%d", &e, &i);
  q=Point(T, e); 
  DeleteChild(T, q, i); 
  printf("层序遍历修改后的树T：\n");
  LevelOrderTraverse(T, visit); 
  DestroyTree(T); 
}


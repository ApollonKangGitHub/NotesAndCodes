// main6-2.cpp ����bo6-3.h��bo6-4.h�ĳ���
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
  printf("������������շ�%d��1���� 0���񣩡�����Ϊ%c���������Ϊ%d��\n", 
  TreeEmpty(T), Root(T), TreeDepth(T));
  CreateTree(T); 
  printf("������T�����շ�%d��1���� 0���񣩡�����Ϊ%c���������Ϊ%d��\n", 
  TreeEmpty(T), Root(T), TreeDepth(T));
  printf("���������T��\n");
  LevelOrderTraverse(T, visit); 
  printf("��������޸ĵĽ���ֵ ��ֵ��");
  scanf("%c%*c%c%*c", &e, &e1);
  Assign(T, e, e1); 
  printf("��������޸ĺ����T��\n");
  LevelOrderTraverse(T, visit); 
  printf("%c��˫����%c��������%c����һ���ֵ���%c��\n", e1, Parent(T, e1), 
  LeftChild(T, e1), RightSibling(T, e1));
  printf("������p��\n");
  CreateTree(p); 
  printf("���������p��\n");
  LevelOrderTraverse(p, visit); 
  printf("����p�嵽��T�У�������T��p��˫�׽�� ������ţ�");
  scanf("%c%d%*c", &e, &i);
  q=Point(T, e); 
  InsertChild(T, q, i, p); 
  printf("��������޸ĺ����T��\n");
  LevelOrderTraverse(T, visit); 
  printf("�ȸ�������T��\n");
  PreOrderTraverse(T, visit); 
  printf("\n���������T��\n");
  PostOrderTraverse(T, visit); 
  printf("\nɾ����T�н��e�ĵ�i��������������e i��");
  scanf("%c%d", &e, &i);
  q=Point(T, e); 
  DeleteChild(T, q, i); 
  printf("��������޸ĺ����T��\n");
  LevelOrderTraverse(T, visit); 
  DestroyTree(T); 
}


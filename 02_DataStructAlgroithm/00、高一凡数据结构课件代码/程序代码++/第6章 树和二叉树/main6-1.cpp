// main6-1.cpp ��������������������������
#define CHAR 1 
//#define CHAR 0 // ���ͣ�����ѡһ������3��
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
  printf("����ն����������շ�%d��1���� 0���񣩡��������=%d��\n", 
  BiTreeEmpty(T), BiTreeDepth(T));
  e1=Root(T); 
  if(e1!=Nil)
    printf("�������ĸ�Ϊ"form"��\n", e1);
  else
    printf("���գ��޸���\n");
#if CHAR 
  printf("�밴����������������磺ab###��ʾaΪ����㣬bΪ�������Ķ���������\n");
#else 
  printf("�밴����������������磺1 2 0 0 0��ʾ1Ϊ����㣬2Ϊ�������Ķ���������\n");
#endif
  CreateBiTree(T); 
  printf("���������������շ�%d��1���� 0���񣩡��������=%d��\n", BiTreeEmpty(T), 
  BiTreeDepth(T));
  e1=Root(T); 
  if(e1!=Nil)
    printf("�������ĸ�Ϊ"form"��\n", e1);
  else
    printf("���գ��޸���\n");
  printf("����ݹ������������\n");
  InOrderTraverse(T, visit); 
  printf("\n����ݹ������������\n");
  PostOrderTraverse(T, visit); 
  printf("\n������һ������ֵ��");
  scanf("%*c"form, &e1);
  p=Point(T, e1); 
  printf("����ֵΪ"form"��\n", Value(p));
  printf("���ı�˽���ֵ����������ֵ��");
  scanf("%*c"form"%*c", &e2); 
  Assign(p, e2); 
  printf("���������������\n");
  LevelOrderTraverse(T, visit); 
  e1=Parent(T, e2); 
  if(e1!=Nil)
    printf(form"��˫����"form"��", e2, e1);
  else
    printf(form"û��˫�ף�", e2);
  e1=LeftChild(T, e2); 
  if(e1!=Nil)
    printf("������"form"��", e1);
  else
    printf("û�����ӣ�");
  e1=RightChild(T, e2); 
  if(e1!=Nil)
    printf("�Һ�����"form"��", e1);
  else
    printf("û���Һ��ӣ�");
  e1=LeftSibling(T, e2); 
  if(e1!=Nil)
    printf("���ֵ���"form"��", e1);
else
    printf("û�����ֵܣ�");
  e1=RightSibling(T, e2); 
  if(e1!=Nil)
    printf("���ֵ���"form"��\n", e1);
  else
    printf("û�����ֵܡ�\n");
  InitBiTree(c); 
  printf("�빹��һ��������Ϊ�յĶ�����c��\n");
#if CHAR 
  printf("�밴����������������磺ab###��ʾaΪ����㣬bΪ�������Ķ���������\n");
#else 
  printf("�밴����������������磺1 2 0 0 0��ʾ1Ϊ����㣬2Ϊ�������Ķ���������\n");
#endif
  CreateBiTree(c); 
  printf("����ݹ����������c��\n");
  InOrderTraverse(c, visit); 
  printf("\n��c�嵽��T�У���������T����c��˫�׽�� cΪ��0�����ң�1��������");
  scanf("%*c"form"%d", &e1, &i);
  p=Point(T, e1); 
  InsertChild(p, i, c);
  
  printf("����ݹ������������\n");
  PreOrderTraverse(T, visit); 
  printf("\nɾ���������������ɾ��������˫�׽�� ��0�����ң�1��������");
  scanf("%*c"form"%d", &e1, &i);
  p=Point(T, e1); 
  DeleteChild(p, i); 
  printf("����ݹ������������\n");
  PreOrderTraverse(T, visit); 
  printf("\n����ǵݹ������������\n");
  InOrderTraverse1(T, visit); 
  printf("����ǵݹ��������������һ�ַ�������\n");
  InOrderTraverse2(T, visit); 
  DestroyBiTree(T); 
}


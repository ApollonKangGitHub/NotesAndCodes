// main1-1.cpp �����������bo1-1.h��������
#include"c1.h" 
// �������пɸ�����Ҫѡ��һ����ֻ��ѡ��һ����������ı��������bo1-1.h
typedef int ElemType; 
//typedef double ElemType; // ���������������ElemType�ڱ�������Ϊ˫�����͡���5��
#include"c1-1.h" 
#include"bo1-1.h" 
#include"func1-1.h" 
void main()
{
  Triplet T;
  ElemType m;
  Status i;
  i=InitTriplet(T, 5, 7, 9); 
//i=InitTriplet(T, 5.0, 7.1, 9.3); // ��ElemTypeΪ˫������ʱ����ȡ���Ͼ䡣��15��
  printf("���ó�ʼ��������i=%d��1���ɹ�����T��3��ֵΪ",i);
  PrintT(T); 
  i=Get(T, 2, m); 
  if(i==OK) 
  { printf("T�ĵ�2��ֵΪ");
    PrintE(m); 
  }
  i=Put(T, 2, 6); 
  if(i==OK) 
  { printf("��T�ĵ�2��ֵ��Ϊ6��T��3��ֵΪ");
    PrintT(T); 
  }
  i=IsAscending(T); 
  printf("���ò�������ĺ�����i=%d��0���� 1���ǣ�\n", i);
  i=IsDescending(T); 
  printf("���ò��Խ���ĺ�����i=%d��0���� 1���ǣ�\n", i);
  if((i=Max(T, m))==OK) 
  { printf("T�е����ֵΪ");
    PrintE(m); 
  }
  if((i=Min(T, m))==OK)
  { printf("T�е���СֵΪ");
    PrintE(m); 
  }
  DestroyTriplet(T); 
  printf("����T��T=%u\n", T);
}


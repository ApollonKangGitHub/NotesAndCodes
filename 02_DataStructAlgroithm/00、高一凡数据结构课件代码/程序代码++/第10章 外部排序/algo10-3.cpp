// algo10-3.cpp ����bo10-1.h�ĳ�������algo10-2.cpp�����д˳���
#include"c1.h"
typedef int KeyType; 
typedef int InfoType; 
#include"c9-1.h" 
#define k 5 
//#define k 3 // 3·�鲢����7��
FILE *fp[k+1]; 
typedef int LoserTree[k];
// [1��k-1]�ǰ������ķ�Ҷ�ӽ�㣬[0]����ʤ�ߣ�����ӦҶ�ӵ����
RedType b[k+1]; 
#define MIN_KEY INT_MIN 
#define MAX_KEY INT_MAX 
#define M 10 
void Print(RedType t)
{ printf("(%d, %d)", t.key, t.otherinfo);
}
#include"bo10-1.h" 
void main()
{
  LoserTree ls; 
  int i;
  char outfile[10], filename[3]; 
  for(i=0; i<k; i++)
  { itoa(i, filename, 10); 
    fp[i]=fopen(filename, "r"); 
  }
  printf("�����������Ĵ��ļ�����");
  scanf("%s", outfile); 
  fp[k]=fopen(outfile, "w"); 
  printf("������ļ�%s�ļ�¼Ϊ��\n", outfile);
  K_Merge(ls); 
  printf("\n"); 
  for(i=0; i<=k; i++)
    fclose(fp[i]); 
}


// c5-3.h ϡ��������Ԫ�����߼����ӵ�˳���洢�ṹ
#define MAX_SIZE 100 
#define MAX_RC 20 
struct Triple 
{ int i, j; 
  ElemType e; 
};
struct RLSMatrix
{ Triple data[MAX_SIZE+1]; 
  int rpos[MAX_RC+1]; 
  int mu, nu, tu; 
};


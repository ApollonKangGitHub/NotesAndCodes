// c5-2.h 稀疏矩阵的三元组顺序表存储结构。在严书第98页
#define MAX_SIZE 100 
struct Triple
{ int i, j; 
  ElemType e; 
};
struct TSMatrix
{ Triple data[MAX_SIZE+1]; 
  int mu, nu, tu; 
};


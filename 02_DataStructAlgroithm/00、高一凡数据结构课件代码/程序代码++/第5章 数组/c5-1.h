// c5-1.h 数组的顺序存储结构。在严书第93页
#define MAX_ARRAY_DIM 8 
struct Array
{ ElemType *base; 
  int dim; 
  int *bounds; 
  int *constants; 
};


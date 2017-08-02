// c7-1.h 图的数组（邻接矩阵）存储结构。在严书第161页
#define INFINITY INT_MAX 
typedef int VRType; 
#define MAX_VERTEX_NUM 26 
enum GraphKind{DG, DN, UDG, UDN}; 
typedef struct 
{ VRType adj; 
  InfoType *info; 
}ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; 
struct MGraph 
{ VertexType vexs[MAX_VERTEX_NUM]; 
  AdjMatrix arcs; 
  int vexnum, arcnum; 
  GraphKind kind; 
};


// c7-2.h 图的邻接表存储结构。在严书第163页
#define MAX_VERTEX_NUM 20 
enum GraphKind{DG, DN, UDG, UDN}; 
struct ArcNode 
{ int adjvex; 
  InfoType *info; 
  ArcNode *nextarc; 
};
typedef struct 
{ VertexType data; 
  ArcNode *firstarc; 
}VNode, AdjList[MAX_VERTEX_NUM];
struct ALGraph 
{ AdjList vertices; 
  int vexnum, arcnum; 
  GraphKind kind; 
};


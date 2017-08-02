// c7-2'.h 图的邻接表存储结构（与单链表的变量类型建立联系）
#define MAX_VERTEX_NUM 20 
enum GraphKind{DG, DN, UDG, UDN}; 
struct ElemType 
{ int adjvex; 
  InfoType *info; 
};
struct ArcNode 
{ ElemType data; 
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
#define LNode ArcNode 
#define next nextarc 
typedef ArcNode *LinkList; 


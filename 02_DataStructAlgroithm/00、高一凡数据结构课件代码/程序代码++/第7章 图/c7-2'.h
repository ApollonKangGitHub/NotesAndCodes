// c7-2'.h ͼ���ڽӱ�洢�ṹ���뵥����ı������ͽ�����ϵ��
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


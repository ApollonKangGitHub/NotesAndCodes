// c7-1.h ͼ�����飨�ڽӾ��󣩴洢�ṹ���������161ҳ
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


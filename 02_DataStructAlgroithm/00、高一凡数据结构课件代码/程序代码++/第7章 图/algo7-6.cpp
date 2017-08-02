// algo7-6.cpp 实现算法7.10、7.11的程序
#include"c1.h"
#include"func7-1.h" 
#include"func7-4.h" 
#include"c7-2'.h" 
#include"bo7-2.h" 
int count, lowcount=1; 
int low[MAX_VERTEX_NUM], lowOrder[MAX_VERTEX_NUM];
// 全局数组，low[]存顶点的low值，lowOrder存顶点求得low值的顺序
int visited[MAX_VERTEX_NUM]; 
void DFSArticul(ALGraph G, int v0)
{ 
  int min, w;
  ArcNode *p;
  visited[v0]=min=++count; 
  for(p=G.vertices[v0].firstarc; p; p=p->nextarc) 
  { w=p->data.adjvex; 
    if(visited[w]==0) 
    { DFSArticul(G, w);
      
      if(low[w]<min) 
        min=low[w]; 
      else if(low[w]>=visited[v0]) 
        printf("%d %s\n", v0, G.vertices[v0].data.name); 
    }
    else if(visited[w]<min) 
      min=visited[w]; 
  }
  low[v0]=min; 
  lowOrder[v0]=lowcount++;
  
}
void FindArticul(ALGraph G)
{ 
  int i, v;
  ArcNode *p;
  count=1; 
  visited[0]=count; 
  for(i=1; i<G.vexnum; i++) 
    visited[i]=0; 
  p=G.vertices[0].firstarc; 
  v=p->data.adjvex; 
  DFSArticul(G, v); 
  if(count<G.vexnum) 
  { 
    printf("%d %s\n", 0, G.vertices[0].data.name); 
    while(p->nextarc) 
    { p=p->nextarc; 
      v=p->data.adjvex;
      if(visited[v]==0) 
        DFSArticul(G, v); 
    }
  }
}
void main()
{
  int i;
  ALGraph g;
  char filename[13]; 
  printf("请输入数据文件名：");
  scanf("%s", filename);
  CreateFromFile(g, filename); 
  Display(g); 
  printf("输出关节点：\n");
  FindArticul(g); 
  printf(" i G.vertices[i].data visited[i] low[i] lowOrder[i]\n"); 
  for(i=0; i<g.vexnum; i++)
    printf("%2d %9s %14d %8d %8d\n", i, g.vertices[i].data.name, 
    visited[i], low[i], lowOrder[i]);
}


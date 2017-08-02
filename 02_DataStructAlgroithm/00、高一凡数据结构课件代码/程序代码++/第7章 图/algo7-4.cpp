// algo7-4.cpp 实现算法7.9的程序
#include"c1.h"
#include"func7-1.h" 
#include"func7-2.h" 
#include"c7-1.h" 
#include"bo7-1.h" 
typedef struct
{ 
  int adjvex; 
  VRType lowcost; 
}minside[MAX_VERTEX_NUM];
int minimum(minside SZ, MGraph G)
{ 
  int i=0, j, k, min;
  while(!SZ[i].lowcost) 
    i++;
  min=SZ[i].lowcost; 
  k=i; 
  for(j=i+1; j<G.vexnum; j++) 
    if(SZ[j].lowcost>0 && SZ[j].lowcost<min) 
    { min=SZ[j].lowcost; 
      k=j; 
    }
  return k; 
}
void MiniSpanTree_PRIM(MGraph G, VertexType u)
{ 
  int i, j, k;
  minside closedge;
  k=LocateVex(G, u); 
  for(j=0; j<G.vexnum; j++) 
  { closedge[j].adjvex=k; 
    closedge[j].lowcost=G.arcs[k][j].adj; 
  }
  closedge[k].lowcost=0; 
  printf("最小代价生成树的各条边为\n");
  for(i=1; i<G.vexnum; i++) 
  { k=minimum(closedge, G); 
    printf("(%s—%s)\n", G.vexs[closedge[k].adjvex].name, G.vexs[k].name);
    
    closedge[k].lowcost=0; 
    for(j=0; j<G.vexnum; j++)
      if(G.arcs[k][j].adj<closedge[j].lowcost) 
      { closedge[j].adjvex=k;
        closedge[j].lowcost=G.arcs[k][j].adj;
      }
  }
}
void main()
{
  MGraph g;
  char filename[13]; 
  printf("请输入数据文件名：");
  scanf("%s", filename);
  CreateFromFile(g, filename, 0); 
  Display(g); 
  MiniSpanTree_PRIM(g, g.vexs[0]);
  
}


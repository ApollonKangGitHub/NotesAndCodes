// algo7-9.cpp 实现算法7.15的程序。迪杰斯特拉算法的实现
#include"c1.h"
#include"func7-1.h" 
#include"func7-2.h" 
#include"c7-1.h" 
#include"bo7-1.h" 
#include"func7-6.h" 
typedef Boolean PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; 
typedef VRType ShortPathTable[MAX_VERTEX_NUM]; 
void ShortestPath_DIJ(MGraph G, int v0, PathMatrix P, ShortPathTable D)
{ 
  
  
  int v, w, i, j;
  VRType min;
  Boolean final[MAX_VERTEX_NUM];
  
  for(v=0; v<G.vexnum; v++)
  { final[v]=FALSE; 
    D[v]=G.arcs[v0][v].adj; 
    for(w=0; w<G.vexnum; w++)
      P[v][w]=FALSE; 
    if(D[v]<INFINITY) 
      P[v][v0]=P[v][v]=TRUE;
      
  }
  D[v0]=0; 
  final[v0]=TRUE; 
  for(i=1; i<G.vexnum; i++) 
  { 
    min=INFINITY; 
    for(w=0; w<G.vexnum; w++) 
      if(!final[w] && D[w]<min) 
      { 
        v=w; 
        min=D[w]; 
      }
    final[v]=TRUE; 
    for(w=0; w<G.vexnum; w++) 
      if(!final[w] && min<INFINITY && G.arcs[v][w].adj<INFINITY && (min+
      G.arcs[v][w].adj<D[w]))
      { 
        D[w]=min+G.arcs[v][w].adj; 
        for(j=0; j<G.vexnum; j++)
        
          P[w][j]=P[v][j];
        P[w][w]=TRUE;
      }
  }
}
void main()
{
  int i, j;
  MGraph g;
  PathMatrix p; 
  ShortPathTable d; 
  Boolean *path;
  int k=0; 
  CreateFromFile(g, "f7-5.txt", 0); 
  Display(g); 
  path=(Boolean*)malloc(g.vexnum*sizeof(Boolean));
  ShortestPath_DIJ(g, k, p, d);
  
  printf("最短路径数组p[i][j]：\n");
  for(i=0; i<g.vexnum; i++)
  { for(j=0; j<g.vexnum; j++)
      printf("%d ", p[i][j]);
    printf("\n");
  }
  printf("%s到各顶点的最短路径长度和依次经过的顶点：\n", g.vexs[k].name);
  for(i=0; i<g.vexnum; i++)
  { if(i!=k && d[i]<INFINITY)
    { printf("%s→%s：%d ", g.vexs[k].name, g.vexs[i].name, d[i]);
      printf("%s→", g.vexs[k].name);
      for(j=0; j<g.vexnum; j++)
        path[j]=p[i][j];
      MakePath(g, path, k, i);
    }
  }
}


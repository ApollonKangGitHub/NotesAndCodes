// algo7-10.cpp ʵ���㷨7.16�ĳ���
#include"c1.h"
#include"func7-1.h" 
#include"func7-2.h" 
#include"c7-1.h" 
#include"bo7-1.h" 
#include"func7-6.h" 
#include"func7-7.h" 
void main()
{
  MGraph g;
  int i, j, k;
  PathMatrix p; 
  DistancMatrix d; 
  Boolean *path;
  CreateFromFile(g, "f7-6.txt", 0);
  for(i=0; i<g.vexnum; i++)
    g.arcs[i][i].adj=0;
    
  Display(g); 
  ShortestPath_FLOYD(g, p, d); 
  printf("d����\n");
  for(i=0; i<g.vexnum; i++)
  { for(j=0; j<g.vexnum; j++)
      if(d[i][j]==INFINITY)
        printf("  ��");
      else
       printf("%4d", d[i][j]);
    printf("\n");
  }
  path=(Boolean*)malloc(g.vexnum*sizeof(Boolean));
  for(i=0; i<g.vexnum; i++)
    for(j=0; j<g.vexnum; j++)
      if(i!=j)
      { printf("%s��%s��p[%d][%d][]=", g.vexs[i].name, g.vexs[j].name, i, j);
        for(k=0; k<g.vexnum; k++)
        { printf("%2d", p[i][j][k]);
          path[k]=p[i][j][k];
        }
        printf(" ��̾���=%2d", d[i][j]);
        printf(" �����Ķ��㣺");
        MakePath(g, path, i, j);
      }
}


// algo7-11.cpp 实现严书图7.33的程序（新增孤立顶点台北）
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
  int i, j, k, q=1;
  PathMatrix p; 
  DistancMatrix d; 
  Boolean *path;
  char filename[8]="map.txt"; 
  CreateFromFile(g, filename, 0); 
  for(i=0; i<g.vexnum; i++)
    g.arcs[i][i].adj=0;
    
  ShortestPath_FLOYD(g, p, d); 
  path=(Boolean*)malloc(g.vexnum*sizeof(Boolean));
  while(q)
  { printf("请选择：1 查询  0 结束\n");
    scanf("%d", &q);
    if(q)
    { printf("城市代码：\n");
      for(i=0; i<g.vexnum; i++)
      { printf("%2d.%-8s", i, g.vexs[i].name);
        if(i%7==6) 
          printf("\n");
      }
      printf("\n请输入要查询的起点城市代码 终点城市代码：");
      scanf("%d%d", &i, &j);
      printf("与%s到%s有关的p矩阵：", g.vexs[i].name, g.vexs[j].name);
      for(k=0; k<g.vexnum; k++)
      { printf("%2d", p[i][j][k]);
        path[k]=p[i][j][k];
      }
      if(d[i][j]==INFINITY) 
        printf("\n%s到%s没有通路\n", g.vexs[i].name, g.vexs[j].name);
      else
      { printf("\n依次经过的城市：");
        MakePath(g, path, i, j); 
        printf("%s到%s的最短距离是%d\n", g.vexs[i].name, g.vexs[j].name, d[i][j]);
      }
    }
  }
}


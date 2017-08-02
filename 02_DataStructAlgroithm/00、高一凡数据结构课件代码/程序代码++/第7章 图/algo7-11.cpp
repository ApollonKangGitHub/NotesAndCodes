// algo7-11.cpp ʵ������ͼ7.33�ĳ���������������̨����
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
  { printf("��ѡ��1 ��ѯ  0 ����\n");
    scanf("%d", &q);
    if(q)
    { printf("���д��룺\n");
      for(i=0; i<g.vexnum; i++)
      { printf("%2d.%-8s", i, g.vexs[i].name);
        if(i%7==6) 
          printf("\n");
      }
      printf("\n������Ҫ��ѯ�������д��� �յ���д��룺");
      scanf("%d%d", &i, &j);
      printf("��%s��%s�йص�p����", g.vexs[i].name, g.vexs[j].name);
      for(k=0; k<g.vexnum; k++)
      { printf("%2d", p[i][j][k]);
        path[k]=p[i][j][k];
      }
      if(d[i][j]==INFINITY) 
        printf("\n%s��%sû��ͨ·\n", g.vexs[i].name, g.vexs[j].name);
      else
      { printf("\n���ξ����ĳ��У�");
        MakePath(g, path, i, j); 
        printf("%s��%s����̾�����%d\n", g.vexs[i].name, g.vexs[j].name, d[i][j]);
      }
    }
  }
}


// algo7-5.cpp 克鲁斯卡尔算法求无向连通网的最小生成树的程序
#include"c1.h"
#include"func7-1.h" 
#include"func7-2.h" 
#include"c7-1.h" 
#include"bo7-1.h" 
struct side 
{ int a, b; 
  VRType weight; 
};
void Kruskal(MGraph G)
{ 
  int set[MAX_VERTEX_NUM], senumber=0, sb, i, j, k;
  side se[MAX_VERTEX_NUM*(MAX_VERTEX_NUM-1)/2]; 
  for(i=0; i<G.vexnum; i++) 
    for(j=i+1; j<G.vexnum; j++) 
      if(G.arcs[i][j].adj<INFINITY) 
      { k=senumber-1; 
        while(k>=0) 
          if(se[k].weight>G.arcs[i][j].adj)
          { 
            se[k+1]=se[k]; 
            k--; 
          }
          else 
            break; 
        se[k+1].a=i; 
        se[k+1].b=j;
        se[k+1].weight=G.arcs[i][j].adj;
        senumber++; 
      }
  printf("i se[i].a se[i].b se[i].weight\n");
  for(i=0; i<senumber; i++)
    printf("%d %4d %7d %9d\n", i, se[i].a, se[i].b, se[i].weight);
  for(i=0; i<G.vexnum; i++) 
    set[i]=i; 
  printf("最小代价生成树的各条边为\n");
  j=0; 
  k=0; 
  while(k<G.vexnum-1) 
  { if(set[se[j].a]!=set[se[j].b]) 
    { printf("(%s-%s)\n", G.vexs[se[j].a].name, G.vexs[se[j].b].name);
      sb=set[se[j].b]; 
      for(i=0; i<G.vexnum; i++) 
        if(set[i]==sb) 
          set[i]=set[se[j].a]; 
      k++; 
    }
    j++; 
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
  Kruskal(g); 
}


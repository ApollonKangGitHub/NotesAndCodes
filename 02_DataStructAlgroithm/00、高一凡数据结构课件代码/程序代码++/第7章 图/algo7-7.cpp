// algo7-7.cpp 输出有向图的一个拓扑序列。实现算法7.12的程序
#include"c1.h"
#include"func7-1.h" 
#include"func7-4.h" 
#include"c7-2'.h" 
#include"bo7-2.h" 
#include"func7-5.h" 
typedef int SElemType; 
#include"c3-1.h" 
#include"bo3-1.h" 
Status TopologicalSort(ALGraph G)
{ 
  
  int i, k, count=0; 
  int indegree[MAX_VERTEX_NUM]; 
  SqStack S;
  ArcNode *p;
  FindInDegree(G, indegree); 
  InitStack(S); 
  for(i=0; i<G.vexnum; i++) 
    if(!indegree[i]) 
      Push(S, i); 
  while(!StackEmpty(S)) 
  { Pop(S, i); 
    printf("%s ", G.vertices[i].data.name); 
    count++; 
    for(p=G.vertices[i].firstarc; p; p=p->nextarc) 
    { k=p->data.adjvex; 
      if(!(--indegree[k])) 
        Push(S, k);
    }
  }
  if(count<G.vexnum) 
  { printf("此有向图有回路\n");
    return ERROR;
  }
  else
  { printf("为一个拓扑序列。\n");
    return OK;
  }
}
void main()
{
  ALGraph f;
  printf("请选择有向图\n");
  CreateGraph(f); 
  Display(f); 
  TopologicalSort(f); 
}


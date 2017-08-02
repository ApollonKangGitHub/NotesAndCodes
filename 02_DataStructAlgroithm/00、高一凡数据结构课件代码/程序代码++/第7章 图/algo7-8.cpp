// algo7-8.cpp 求关键路径。实现算法7.13、7.14的程序
#include"c1.h"
#include"func7-1.h" 
#include"func7-4.h" 
#include"c7-2'.h" 
#include"bo7-2.h" 
#include"func7-5.h" 
typedef int SElemType; 
#include"c3-1.h" 
#include"bo3-1.h" 
int ve[MAX_VERTEX_NUM]; 
Status TopologicalOrder(ALGraph G, SqStack &T)
{ 
  
  
  int i, k, count=0; 
  int indegree[MAX_VERTEX_NUM]; 
  SqStack S;
  ArcNode *p;
  FindInDegree(G, indegree); 
  InitStack(S); 
  printf("拓扑序列：");
  for(i=0; i<G.vexnum; i++) 
    if(!indegree[i]) 
      Push(S, i); 
  InitStack(T); 
  for(i=0; i<G.vexnum; i++) 
    ve[i]=0;
  while(!StackEmpty(S)) 
  { Pop(S, i); 
    Visit(G.vertices[i].data); 
    Push(T, i); 
    count++; 
    for(p=G.vertices[i].firstarc; p; p=p->nextarc)
    { 
      k=p->data.adjvex; 
      if(--indegree[k]==0) 
        Push(S, k);
      if(ve[i]+p->data.info->weight>ve[k])
      
        ve[k]=ve[i]+p->data.info->weight;
        
    }   
  }
  if(count<G.vexnum)
  { printf("此有向网有回路\n");
    return ERROR;
  }
  else
    return OK;
}
void Visitel(int i)
{ printf("%3d", i);
}
Status CriticalPath(ALGraph G)
{ 
  SqStack T;
  int i, j, k;
  ArcNode *p;
  int ee[MAX_VERTEX_NUM]; 
  int el[MAX_VERTEX_NUM]; 
  int vl[MAX_VERTEX_NUM]; 
  if(!TopologicalOrder(G, T)) 
    return ERROR;
  j=ve[0]; 
  for(i=1; i<G.vexnum; i++) 
    if(ve[i]>j)
      j=ve[i]; 
  for(i=0; i<G.vexnum; i++) 
    vl[i]=j; 
  while(!StackEmpty(T)) 
    for(Pop(T, j), p=G.vertices[j].firstarc; p; p=p->nextarc)
    { 
      
      k=p->data.adjvex; 
      if(vl[k]-p->data.info->weight<vl[j])
      
        vl[j]=vl[k]-p->data.info->weight;
        
    }   
  printf("\ni  ve  vl\n");
  for(i=0; i<G.vexnum; i++) 
  { printf("%d ", i); 
    Visitel(ve[i]); 
    Visitel(vl[i]); 
    if(ve[i]==vl[i]) 
      printf(" 关键路径经过的顶点");
    printf("\n");
  }
  printf("j   k 权值 ee el\n"); 
  for(j=0; j<G.vexnum; j++) 
    for(p=G.vertices[j].firstarc; p; p=p->nextarc)
    { 
      k=p->data.adjvex; 
      ee[k]=ve[j]; 
      el[k]=vl[k]-p->data.info->weight;
      
      printf("%s→%s", G.vertices[j].data.name, G.vertices[k].data.name);
      OutputArc(p->data.info); 
      Visitel(ee[k]); 
      Visitel(el[k]); 
      if(ee[k]==el[k]) 
        printf(" 关键活动");
      printf("\n");
    }
  return OK;
}
void main()
{
  ALGraph h;
  printf("请选择有向网\n");
  CreateGraph(h); 
  Display(h); 
  CriticalPath(h); 
}


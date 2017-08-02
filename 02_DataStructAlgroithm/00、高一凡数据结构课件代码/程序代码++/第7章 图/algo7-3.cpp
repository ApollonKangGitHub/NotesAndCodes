// algo7-3.cpp 调用算法7.7和7.8
#include"c1.h"
#include"func7-1.h" 
#include"func7-4.h" 
typedef VertexType TElemType; 
#include"c6-2.h" 
#include"bo6-4.h" 
#include"c7-2'.h" 
Boolean visited[MAX_VERTEX_NUM]; 
#include"bo7-2.h" 
typedef ALGraph Graph; 
void DFSTree(Graph G, int v, CSTree &T)
{ 
  Boolean first=TRUE; 
  int w;
  CSTree p, q; 
  visited[v]=TRUE; 
  for(w=FirstAdjVex(G, v); w>=0; w=NextAdjVex(G, v, w)) 
    if(!visited[w]) 
    { p=(CSTree)malloc(sizeof(CSNode)); 
      p->data=GetVex(G, w); 
      p->firstchild=NULL; 
      p->nextsibling=NULL;
      if(first) 
      { T->firstchild=p; 
        first=FALSE; 
      }
      else 
        q->nextsibling=p; 
                             
      q=p; 
      DFSTree(G, w, q); 
    }
}
void DFSForest(Graph G, CSTree &T)
{ 
  CSTree p, q; 
  int v;
  T=NULL; 
  for(v=0; v<G.vexnum; v++) 
    visited[v]=FALSE; 
  for(v=0; v<G.vexnum; v++) 
    if(!visited[v]) 
    { 
      p=(CSTree)malloc(sizeof(CSNode)); 
      p->data=GetVex(G, v); 
      p->firstchild=NULL; 
      p->nextsibling=NULL; 
      if(!T) 
        T=p; 
      else 
        q->nextsibling=p; 
      q=p; 
      DFSTree(G, v, p); 
    }
}
void main()
{
  Graph g;
  CSTree t;
  printf("请选择无向图\n");
  CreateGraph(g); 
  Display(g); 
  DFSForest(g, t); 
  printf("先序遍历生成森林：\n");
  PreOrderTraverse(t, Visit); 
  printf("\n");
}


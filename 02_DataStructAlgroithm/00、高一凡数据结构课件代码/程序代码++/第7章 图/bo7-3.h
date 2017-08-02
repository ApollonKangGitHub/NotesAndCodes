// bo7-3.h Ëã·¨7.4¡«7.6
Boolean visite[MAX_VERTEX_NUM]; 
void(*VisitFunc)(VertexType); 
void DFS(Graph G, int v)
{ 
  int w;
  visite[v]=TRUE; 
  VisitFunc(GetVex(G, v)); 
  for(w=FirstAdjVex(G, v); w>=0; w=NextAdjVex(G, v, w))
  
    if(!visite[w]) 
      DFS(G, w); 
}
void DFSTraverse(Graph G, void(*Visit)(VertexType))
{ 
  
  int v;
  VisitFunc=Visit; 
  for(v=0; v<G.vexnum; v++) 
    visite[v]=FALSE; 
  for(v=0; v<G.vexnum; v++) 
    if(!visite[v]) 
      DFS(G, v); 
  printf("\n");
}
typedef int QElemType; 
#include"c3-2.h" 
#include"bo3-2.h" 
void BFSTraverse(Graph G, void(*Visit)(VertexType))
{ 
  
  int v, u, w;
  LinkQueue Q; 
  for(v=0; v<G.vexnum; v++) 
    visite[v]=FALSE; 
  InitQueue(Q); 
  for(v=0; v<G.vexnum; v++) 
    if(!visite[v]) 
    { visite[v]=TRUE; 
      Visit(GetVex(G, v)); 
      EnQueue(Q, v); 
      while(!QueueEmpty(Q)) 
      { DeQueue(Q, u); 
        for(w=FirstAdjVex(G,u); w>=0; w=NextAdjVex(G,u,w))
          if(!visite[w]) 
          { visite[w]=TRUE; 
            Visit(GetVex(G, w)); 
            EnQueue(Q, w); 
          }
      }
    }
  printf("\n");
}


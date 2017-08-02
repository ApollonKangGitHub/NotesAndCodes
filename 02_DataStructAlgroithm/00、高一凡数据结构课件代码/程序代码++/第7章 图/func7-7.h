// func7-7.h 算法7.16，algo7-10.cpp和algo7-11.cpp用到
typedef Boolean PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM][MAX_VERTEX_NUM];
// 3维数组
typedef VRType DistancMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; 
void ShortestPath_FLOYD(MGraph G, PathMatrix P, DistancMatrix D)
{ 
  
  int u, v, w, i;
  for(v=0; v<G.vexnum; v++) 
    for(w=0; w<G.vexnum; w++)
    { D[v][w]=G.arcs[v][w].adj; 
      for(u=0; u<G.vexnum; u++)
        P[v][w][u]=FALSE; 
      if(D[v][w]<INFINITY) 
        P[v][w][v]=P[v][w][w]=TRUE; 
    }
  for(u=0; u<G.vexnum; u++)
    for(v=0; v<G.vexnum; v++)
      for(w=0; w<G.vexnum; w++)
        if(u!=v && u!=w && v!=w && D[v][u]<INFINITY && D[u][w]<INFINITY &&
        D[v][u]+D[u][w]<D[v][w])
        { 
          D[v][w]=D[v][u]+D[u][w]; 
          for(i=0; i<G.vexnum; i++)
            P[v][w][i]=P[v][u][i] || P[u][w][i];
            
        }
}


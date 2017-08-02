// func7-5.h algo7-7.cpp��algo7-8.cppҪ����
void FindInDegree(ALGraph G, int indegree[])
{ 
  int i;
  ArcNode *p;
  for(i=0; i<G.vexnum; i++) 
    indegree[i]=0; 
  for(i=0; i<G.vexnum; i++) 
  { p=G.vertices[i].firstarc; 
    while(p) 
    { indegree[p->data.adjvex]++; 
      p=p->nextarc; 
    }
  }
}


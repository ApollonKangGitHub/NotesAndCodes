// func7-6.h
void MakePath(MGraph G, Boolean P[], int i,  int j)
{ 
  int k, MinNum, begin=i; 
  VRType Min; 
  while(begin!=j) 
  { Min=INFINITY; 
    for(k=0; k<G.vexnum; k++) 
      if(G.arcs[begin][k].adj<Min && P[k])
      { 
        Min=G.arcs[begin][k].adj; 
        MinNum=k; 
      }
    if(Min==INFINITY) 
      break; 
    printf("%s", G.vexs[MinNum].name); 
    if(MinNum!=j) 
      printf("¡ú");
    P[MinNum]=FALSE; 
    begin=MinNum; 
  }
  printf("\n");
}


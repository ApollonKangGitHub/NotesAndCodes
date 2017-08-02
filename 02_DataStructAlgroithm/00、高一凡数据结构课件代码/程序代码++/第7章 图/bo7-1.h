// bo7-1.h ͼ���ڽӾ���洢���洢�ṹ��c7-1.h���壩�Ļ���������17�����������㷨7.1��7.2
int LocateVex(MGraph G, VertexType u)
{ 
  
  int i;
  for(i=0; i<G.vexnum; i++) 
    if(strcmp(u.name, G.vexs[i].name)==0) 
      return i; 
  return -1; 
}
void CreateDG(MGraph &G)
{ 
  int i, j, k, IncInfo; 
  VertexType v1, v2; 
  printf("����������ͼG�Ķ�����,����,���Ƿ������Ϣ���ǣ�1 ��0����");
  scanf("%d,%d,%d", &G.vexnum, &G.arcnum, &IncInfo);
  printf("������%d�������ֵ������<%d���ַ�����\n", G.vexnum, MAX_NAME);
  for(i=0; i<G.vexnum; i++) 
    Input(G.vexs[i]); 
  for(i=0; i<G.vexnum; i++) 
    for(j=0; j<G.vexnum; j++)
    { G.arcs[i][j].adj=0; 
      G.arcs[i][j].info=NULL; 
    }
  printf("������%d�����Ļ�β ��ͷ��\n", G.arcnum);
  for(k=0; k<G.arcnum; k++)
  { scanf("%s%s%*c", v1.name, v2.name); 
    i=LocateVex(G, v1); 
    j=LocateVex(G, v2); 
    G.arcs[i][j].adj=1; 
    if(IncInfo) 
      InputArc(G.arcs[i][j].info);
      
  }
  G.kind=DG;
}
void CreateDN(MGraph &G)
{ 
  int i, j, k, IncInfo; 
  VRType w; 
  VertexType v1, v2; 
  printf("������������G�Ķ�����,����,���Ƿ������Ϣ���ǣ�1 ��0����");
  scanf("%d,%d,%d", &G.vexnum, &G.arcnum, &IncInfo);
  printf("������%d�������ֵ������<%d���ַ�����\n", G.vexnum, MAX_NAME);
  for(i=0; i<G.vexnum; i++) 
    Input(G.vexs[i]); 
  for(i=0; i<G.vexnum; i++) 
    for(j=0; j<G.vexnum; j++)
    { G.arcs[i][j].adj=INFINITY; 
      G.arcs[i][j].info=NULL; 
    }
  printf("������%d�����Ļ�β ��ͷ Ȩֵ��\n", G.arcnum);
  for(k=0; k<G.arcnum; k++)
  { scanf("%s%s%d%*c", v1.name, v2.name, &w); 
    i=LocateVex(G, v1); 
    j=LocateVex(G, v2); 
    G.arcs[i][j].adj=w; 
    if(IncInfo) 
      InputArc(G.arcs[i][j].info);
      
  }
  G.kind=DN;
}
void CreateUDG(MGraph &G)
{ 
  int i, j, k, IncInfo; 
  VertexType v1, v2; 
  printf("����������ͼG�Ķ�����,����,���Ƿ������Ϣ���ǣ�1 ��0����");
  scanf("%d,%d,%d", &G.vexnum, &G.arcnum, &IncInfo);
  printf("������%d�������ֵ������<%d���ַ�����\n", G.vexnum, MAX_NAME);
  for(i=0; i<G.vexnum; i++) 
    Input(G.vexs[i]); 
  for(i=0; i<G.vexnum; i++) 
    for(j=0; j<G.vexnum; j++)
    { G.arcs[i][j].adj=0; 
      G.arcs[i][j].info=NULL; 
    }
  printf("������%d���ߵĶ���1 ����2��\n", G.arcnum);
  for(k=0; k<G.arcnum; k++)
  { scanf("%s%s%*c", v1.name, v2.name); 

    i=LocateVex(G, v1); 
    j=LocateVex(G, v2); 
    G.arcs[i][j].adj=1; 
    if(IncInfo) 
      InputArc(G.arcs[i][j].info);
      
    G.arcs[j][i]=G.arcs[i][j]; 
  }
  G.kind=UDG;
}
void CreateUDN(MGraph &G)
{ 
  int i, j, k, IncInfo; 
  VRType w; 
  VertexType v1, v2; 
  printf("������������G�Ķ�����,����,���Ƿ������Ϣ���ǣ�1 ��0����");
  scanf("%d,%d,%d", &G.vexnum, &G.arcnum, &IncInfo);
  printf("������%d�������ֵ������<%d���ַ�����\n", G.vexnum, MAX_NAME);
  for(i=0; i<G.vexnum; i++) 
    Input(G.vexs[i]); 
  for(i=0; i<G.vexnum; i++) 
    for(j=0; j<G.vexnum; j++)
    { G.arcs[i][j].adj=INFINITY; 
      G.arcs[i][j].info=NULL; 
    }
  printf("������%d���ߵĶ���1 ����2 Ȩֵ��\n", G.arcnum);
  for(k=0; k<G.arcnum; k++)
  { scanf("%s%s%d%*c", v1.name, v2.name, &w); 
    i=LocateVex(G, v1); 
    j=LocateVex(G, v2); 
    G.arcs[i][j].adj=w; 
    if(IncInfo) 
      InputArc(G.arcs[i][j].info);
      
    G.arcs[j][i]=G.arcs[i][j]; 
  }
  G.kind=UDN;
}
void CreateGraph(MGraph &G)
{ 
  printf("������ͼG�����ͣ�����ͼ��0 ��������1 ����ͼ��2 ��������3����");
  scanf("%d", &G.kind);
  switch(G.kind) 
  { case  DG: CreateDG(G); 
              break;
    case  DN: CreateDN(G); 
              break;
    case UDG: CreateUDG(G); 
              break;
    case UDN: CreateUDN(G); 
  }
}
VertexType GetVex(MGraph G, int v)
{ 
  if(v>=G.vexnum || v<0) 
    exit(OVERFLOW);
  return G.vexs[v]; 
}
Status PutVex(MGraph &G, VertexType v, VertexType value)
{ 
  int k=LocateVex(G, v); 
  if(k<0) 
    return ERROR;
  G.vexs[k]=value; 
  return OK;
}
int FirstAdjVex(MGraph G, int v)
{ 
  
  int i;
  VRType j=0; 
  if(G.kind%2) 
    j=INFINITY;
  for(i=0; i<G.vexnum; i++) 
    if(G.arcs[v][i].adj!=j) 
      return i; 
  return -1; 
}
int NextAdjVex(MGraph G, int v, int w)
{ 
  
  
  int i;
  VRType j=0; 
  if(G.kind%2) 
    j=INFINITY;
  for(i=w+1; i<G.vexnum; i++) 
    if(G.arcs[v][i].adj!=j) 
      return i; 
  return -1; 
}
void InsertVex(MGraph &G, VertexType v)
{ 
  
  int i;
  VRType j=0; 
  if(G.kind%2) 
    j=INFINITY;
  G.vexs[G.vexnum]=v; 
  for(i=0; i<=G.vexnum; i++) 
  { G.arcs[G.vexnum][i].adj=G.arcs[i][G.vexnum].adj=j;
    
    G.arcs[G.vexnum][i].info=G.arcs[i][G.vexnum].info=NULL; 
  }
  G.vexnum++; 
}
Status InsertArc(MGraph &G, VertexType v, VertexType w)
{ 
  
  int i, v1, w1;
  v1=LocateVex(G, v); 
  w1=LocateVex(G, w); 
  if(v1<0 || w1<0) 
    return ERROR;
  if(G.kind%2 && G.arcs[v1][w1].adj==INFINITY || G.kind%2==0 && G.arcs[v1][w1].adj==0) 
    G.arcnum++; 
  if(G.kind%2) 
  { printf("������˻���Ȩֵ��");
    scanf("%d", &G.arcs[v1][w1].adj);
  }
  else 
    G.arcs[v1][w1].adj=1;
  printf("�Ƿ��иû��������Ϣ��0���� 1���У���");
  scanf("%d%*c", &i);
  if(i)
    InputArc(G.arcs[v1][w1].info); 
  if(G.kind>1) 
    G.arcs[w1][v1]=G.arcs[v1][w1]; 
  return OK;
}
Status DeleteArc(MGraph &G, VertexType v, VertexType w)
{ 
  
  int v1, w1;
  VRType j=0; 
  if(G.kind%2) 
    j=INFINITY;
  v1=LocateVex(G, v); 
  w1=LocateVex(G, w); 
  if(v1<0 || w1<0) 
    return ERROR;
  if(G.arcs[v1][w1].adj!=j) 
  { G.arcs[v1][w1].adj=j; 
    if(G.arcs[v1][w1].info) 
    { free(G.arcs[v1][w1].info); 
      G.arcs[v1][w1].info=NULL; 
    }
    if(G.kind>=2) 
      G.arcs[w1][v1]=G.arcs[v1][w1]; 
    G.arcnum--; 
  }
  return OK;
}
Status DeleteVex(MGraph &G, VertexType v)
{ 
  int i, j, k;
  k=LocateVex(G, v); 
  if(k<0) 
    return ERROR;
  for(i=0; i<G.vexnum; i++)
    DeleteArc(G, v, G.vexs[i]); 
  if(G.kind<2) 
    for(i=0; i<G.vexnum; i++)
      DeleteArc(G, G.vexs[i], v); 
  for(j=k+1; j<G.vexnum; j++)
    G.vexs[j-1]=G.vexs[j]; 
  for(i=0; i<G.vexnum; i++)
    for(j=k+1; j<G.vexnum; j++)
      G.arcs[i][j-1]=G.arcs[i][j]; 
  for(i=0; i<G.vexnum-1; i++)
    for(j=k+1; j<G.vexnum; j++)
      G.arcs[j-1][i]=G.arcs[j][i]; 
  G.vexnum--; 
  return OK;
}
void DestroyGraph(MGraph &G)
{ 
  int i;
  for(i=G.vexnum-1; i>=0; i--) 
    DeleteVex(G, G.vexs[i]);
}
void Display(MGraph G)
{ 
  int i, j;
  char s[7]="������", s1[3]="��";
  switch(G.kind)
  { case  DG: strcpy(s, "����ͼ");
              strcpy(s1, "��");
              break;
    case  DN: strcpy(s, "������");
              strcpy(s1, "��");
              break;
    case UDG: strcpy(s, "����ͼ");
    case UDN: ;
  }
  printf("%d������%d��%s��%s�����������ǣ�", G.vexnum, G.arcnum, s1, s);
  for(i=0; i<G.vexnum; i++)
    Visit(GetVex(G, i)); 
  printf("\nG.arcs.adj��\n");
  for(i=0; i<G.vexnum; i++) 
  { for(j=0; j<G.vexnum; j++)
	  if(G.arcs[i][j].adj==INFINITY)
		printf("  ��");
	  else
         printf("%4d", G.arcs[i][j].adj);
     printf("\n");
  }
  printf("G.arcs.info��\n"); 
  if(G.kind<2) 
    printf(" ��β  ��ͷ ��%s����Ϣ��\n", s1);
  else 
    printf("����1 ����2 ��%s����Ϣ��\n", s1);
  for(i=0; i<G.vexnum; i++)
    if(G.kind<2) 
    { for(j=0; j<G.vexnum; j++)
        if(G.arcs[i][j].info)
        { printf("%5s%5s ", G.vexs[i].name, G.vexs[j].name);
          OutputArc(G.arcs[i][j].info); 
        }
    } 
    else 
      for(j=i+1; j<G.vexnum; j++)
        if(G.arcs[i][j].info)
        { printf("%5s %5s ", G.vexs[i].name, G.vexs[j].name);
          OutputArc(G.arcs[i][j].info); 
        }
}
void CreateFromFile(MGraph &G, char* filename, int IncInfo)
{ 
  int i, j, k;
  VRType w=0; 
  VertexType v1, v2; 
  FILE *f; 
  f=fopen(filename, "r"); 
  fscanf(f, "%d", &G.kind); 
  if(G.kind%2) 
    w=INFINITY;
  fscanf(f, "%d", &G.vexnum); 
  for(i=0; i<G.vexnum; i++)
    InputFromFile(f, G.vexs[i]); 
  fscanf(f, "%d", &G.arcnum); 
  for(i=0; i<G.vexnum; i++) 
    for(j=0; j<G.vexnum; j++)
    { G.arcs[i][j].adj=w; 
      G.arcs[i][j].info=NULL; 
    }
  if(!(G.kind%2)) 
    w=1;
  for(k=0; k<G.arcnum; k++) 
  { fscanf(f, "%s%s", v1.name, v2.name); 
    if(G.kind%2) 
      fscanf(f, "%d", &w); 
    i=LocateVex(G, v1); 
    j=LocateVex(G, v2); 
    G.arcs[i][j].adj=w; 
    if(IncInfo) 
      InputArcFromFile(f, G.arcs[i][j].info);
      
    if(G.kind>1) 
      G.arcs[j][i]=G.arcs[i][j]; 
  }
  fclose(f); 
}


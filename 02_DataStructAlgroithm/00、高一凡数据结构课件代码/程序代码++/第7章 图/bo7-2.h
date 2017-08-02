// bo7-2.h ͼ���ڽӱ�洢���洢�ṹ��c7-2'.h���壩�Ļ���������14����
#include"bo2-3.h" 
#include"func2-4.h" 
int LocateVex(ALGraph G, VertexType u)
{ 
  
  int i;
  for(i=0; i<G.vexnum; i++) 
    if(strcmp(u.name, G.vertices[i].data.name)==0) 
      return i; 
  return -1; 
}
void CreateGraph(ALGraph &G)
{ 
  int i, j, k;
  VertexType v1, v2; 
  ElemType e; 
  char s[3]="��";
  printf("������ͼ�����ͣ�����ͼ��0 ��������1 ����ͼ��2 ��������3����");
  scanf("%d", &G.kind);
  if(G.kind<2) 
    strcpy(s, "��");
  printf("������ͼ�Ķ�����,������");
  scanf("%d,%d", &G.vexnum, &G.arcnum);
  printf("������%d�������ֵ������<%d���ַ�����\n", G.vexnum, MAX_NAME);
  for(i=0; i<G.vexnum; i++) 
  { Input(G.vertices[i].data); 
    G.vertices[i].firstarc=NULL; 
  }
  printf("������%d��%s��", G.arcnum, s);
  switch(G.kind)
  { case  DG: printf("��β ��ͷ��\n"); 
              break;
    case  DN: printf("��β ��ͷ ������Ϣ��\n");
              break;
    case UDG: printf("����1 ����2��\n"); 
              break;
    case UDN: printf("����1 ����2 �ߵ���Ϣ��\n");
  }
  for(k=0; k<G.arcnum; k++) 
  { scanf("%s%s", v1.name, v2.name); 
    i=LocateVex(G, v1); 
    j=LocateVex(G, v2); 
    e.info=NULL; 
    if(G.kind%2) 
      InputArc(e.info); 
    e.adjvex=j; 
    ListInsert(G.vertices[i].firstarc, 1, e);
    
    if(G.kind>=2) 
    { e.adjvex=i; 
      ListInsert(G.vertices[j].firstarc, 1, e);
    }
  }
}
void CreateFromFile(ALGraph &G, char* filename)
{ 
  int i, j, k;
  VertexType v1, v2; 
  ElemType e; 
  FILE *f; 
  f=fopen(filename, "r"); 
  fscanf(f, "%d", &G.kind); 
  fscanf(f, "%d", &G.vexnum); 
  for(i=0; i<G.vexnum; i++) 
  { InputFromFile(f, G.vertices[i].data); 
    G.vertices[i].firstarc=NULL; 
  }
  fscanf(f, "%d", &G.arcnum); 
  for(k=0; k<G.arcnum; k++) 
  { fscanf(f, "%s%s", v1.name, v2.name); 
    i=LocateVex(G, v1); 
    j=LocateVex(G, v2); 
    e.info=NULL; 
    if(G.kind%2) 
      InputArcFromFile(f, e.info);
      
    e.adjvex=j; 
    ListInsert(G.vertices[i].firstarc, 1, e);
    
    if(G.kind>=2) 
    { e.adjvex=i; 
      ListInsert(G.vertices[j].firstarc, 1, e);
    }
  }
  fclose(f); 
}
VertexType GetVex(ALGraph G, int v)
{ 
  if(v>=G.vexnum || v<0) 
    exit(OVERFLOW);
  return G.vertices[v].data; 
}
Status PutVex(ALGraph &G, VertexType v, VertexType value)
{ 
  int k=LocateVex(G, v); 
  if(k!=-1) 
  { G.vertices[k].data=value; 
    return OK;
  }
  return ERROR; 
}
int FirstAdjVex(ALGraph G, int v)
{ 
  
  ArcNode *p=G.vertices[v].firstarc; 
  if(p) 
    return p->data.adjvex; 
  else
    return -1; 
}
Status equalvex(ElemType a, ElemType b)
{ 
  if(a.adjvex==b.adjvex) 
    return OK;
  else
    return ERROR;
}
int NextAdjVex(ALGraph G, int v, int w)
{ 
  
  LinkList p, p1; 
  ElemType e; 
  e.adjvex=w;
  p=Point(G.vertices[v].firstarc, e, equalvex, p1);
  
  if(!p || !p->next) 
    return -1;
  else 
    return p->next->data.adjvex; 
}
void InsertVex(ALGraph &G, VertexType v)
{ 
  
  G.vertices[G.vexnum].data=v; 
  G.vertices[G.vexnum].firstarc=NULL; 
  G.vexnum++; 
}
Status InsertArc(ALGraph &G, VertexType v, VertexType w)
{ 
  
  ElemType e; 
  int i, j;
  char s1[3]="��", s2[3]="��"; 
  if(G.kind<2) 
  { strcpy(s1, "��");
    strcpy(s2, "��");
  }
  i=LocateVex(G, v); 
  j=LocateVex(G, w); 
  if(i<0 || j<0) 
    return ERROR;
  G.arcnum++; 
  e.adjvex=j; 
  e.info=NULL; 
  if(G.kind%2) 
  { printf("������%s%s%s%s����Ϣ��", s1, v.name, s2, w.name);
    InputArc(e.info); 
  }
  ListInsert(G.vertices[i].firstarc, 1, e); 
  if(G.kind>=2) 
  { e.adjvex=i; 
    ListInsert(G.vertices[j].firstarc, 1, e); 
  }
  return OK;
}
Status DeleteArc(ALGraph &G, VertexType v, VertexType w)
{ 
  
  int i, j, n;
  ElemType e; 
  i=LocateVex(G, v); 
  j=LocateVex(G, w); 
  if(i<0 || j<0 || i==j) 
    return ERROR;
  e.adjvex=j; 
  n=LocateElem(G.vertices[i].firstarc, e, equalvex);
  
  if(n) 
  { ListDelete(G.vertices[i].firstarc, n, e);
    
    G.arcnum--; 
    if(G.kind%2) 
      free(e.info); 
    if(G.kind>=2) 
    { e.adjvex=i; 
      n=LocateElem(G.vertices[j].firstarc, e, equalvex);
      
      ListDelete(G.vertices[j].firstarc, n, e);
      
    }
    return OK;
  }
  else 
    return ERROR;
}
Status DeleteVex(ALGraph &G, VertexType v)
{ 
  int i, k;
  LinkList p; 
  k=LocateVex(G, v); 
  if(k<0) 
    return ERROR;
  for(i=0; i<G.vexnum; i++)
    DeleteArc(G, v, G.vertices[i].data); 
  if(G.kind<2) 
    for(i=0; i<G.vexnum; i++)
      DeleteArc(G, G.vertices[i].data, v); 
  for(i=0; i<G.vexnum; i++) 
  { p=G.vertices[i].firstarc; 
    while(p) 
    { if(p->data.adjvex>k) 
        p->data.adjvex--; 
      p=p->next; 
    }
  }
  for(i=k+1; i<G.vexnum; i++)
    G.vertices[i-1]=G.vertices[i]; 
  G.vexnum--; 
  return OK;
}
void DestroyGraph(ALGraph &G)
{ 
  int i;
  for(i=G.vexnum-1; i>=0; i--) 
    DeleteVex(G, G.vertices[i].data);
}
void Display(ALGraph G)
{ 
  int i;
  ArcNode *p;
  char s1[3]="��", s2[3]="��"; 
  if(G.kind<2) 
  { strcpy(s1, "��");
    strcpy(s2, "��");
  }
  switch(G.kind)
  { case  DG: printf("����ͼ\n");
              break;
    case  DN: printf("������\n");
              break;
    case UDG: printf("����ͼ\n");
              break;
    case UDN: printf("������\n");
  }
  printf("%d�����㣬�����ǣ�", G.vexnum);
  for(i=0; i<G.vexnum; i++)
    Visit(GetVex(G, i)); 
  printf("\n%d��%s��\n", G.arcnum, s1);
  for(i=0; i<G.vexnum; i++)
  { p=G.vertices[i].firstarc; 
    while(p) 
    { if(G.kind<=1 || i<p->data.adjvex) 
      { printf(" %s%s%s", G.vertices[i].data.name, s2, 
         G.vertices[p->data.adjvex].data.name);
        if(G.kind%2) 
          OutputArc(p->data.info); 
      }
      p=p->nextarc; 
    }
    printf("\n");
  }
}


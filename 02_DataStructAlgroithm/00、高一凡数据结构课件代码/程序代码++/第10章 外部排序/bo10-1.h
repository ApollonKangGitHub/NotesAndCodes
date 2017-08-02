// bo10-1.h k路平衡归并的函数，包括算法11.1～11.3
void input(int i, RedType &a)
{ 
  fscanf(fp[i], "%d %d", &a.key, &a.otherinfo);
}
void output(RedType a)
{ 
  static int col=0; 
  fprintf(fp[k], "%d %d\n", a.key, a.otherinfo); 
  Print(a); 
  if(++col%M==0)
    printf("\n"); 
}
void Adjust(LoserTree ls, int s) 
{ 
  int i, t;
  t=(s+k)/2; 
  while(t>0) 
  { if(b[s].key>b[ls[t]].key) 
    { i=s; 
      s=ls[t]; 
      ls[t]=i; 
    }
    t=t/2; 
  }
  ls[0]=s; 
}
void CreateLoserTree(LoserTree ls)
{ 
  
  int i;
  b[k].key=MIN_KEY; 
  for(i=1; i<k; i++)
    ls[i]=k; 
  for(i=k-1; i>=0; i--) 
    Adjust(ls, i); 
}
void K_Merge(LoserTree ls)
{ 
  
  
  int i;
  for(i=0; i<k; i++) 
  { input(i, b[i]); 
    if(feof(fp[i])) 
      b[i].key=MAX_KEY; 
  }
  CreateLoserTree(ls);
  
  while(b[ls[0]].key!=MAX_KEY) 
  { output(b[ls[0]]); 
    input(ls[0], b[ls[0]]); 
    if(feof(fp[ls[0]])) 
      b[ls[0]].key=MAX_KEY; 
    Adjust(ls, ls[0]);
    
  }
}


// bo8-5.h 双链键树的基本操作，包括算法9.15
void InitDSTable(DLTree &DT)
{ 
  DT=(DLTree)malloc(sizeof(DLTNode)); 
  DT->kind=BRANCH; 
  DT->first=DT->next=NULL;
}
void DestroyDSTable(DLTree &DT)
{ 
  if(DT) 
  { if(DT->kind==BRANCH) 
      DestroyDSTable(DT->first); 
    DestroyDSTable(DT->next); 
    free(DT); 
    DT=NULL; 
  }
}
Record* SearchDLTree(DLTree T, KeyType K)
{ 
  
  DLTree p=T->first; 
  int i=0;
  while(p && i<K.num) 
  { while(p && p->symbol<K.ch[i]) 
      p=p->next; 
    if(p && p->symbol==K.ch[i])
    { p=p->first; 
      i++; 
    }
    else
      p=NULL;
  } 
  if(p && p->kind==LEAF) 
    return p->infoptr; 
  else 
    return NULL;
}
Status InsertDSTable(DLTree &DT, Record* r)
{ 
  
  DLTree q=DT, p=DT->first, ap;
  
  int i=0;
  KeyType K=r->key;
  while(p && i<K.num) 
  { while(p && p->symbol<K.ch[i]) 
    { q=p; 
      p=p->next; 
    }
    if(p && p->symbol==K.ch[i]) 
    { q=p; 
      p=p->first; 
      i++; 
    }
    else
      break;
  }
  if(p && p->kind==LEAF) 
    return FALSE;
  else
  {
    ap=(DLTree)malloc(sizeof(DLTNode)); 
    if(q->first==p)
      q->first=ap; 
    else 
      q->next=ap; 
    if(i==K.num) 
    {
      ap->next=p;
      ap->symbol=Nil;
      ap->kind=LEAF;
      ap->infoptr=r;
      return TRUE;
    }
    else 
    {
      ap->next=p; 
      ap->symbol=K.ch[i]; 
      ap->kind=BRANCH; 
      p=ap; 
      ap=(DLTree)malloc(sizeof(DLTNode)); 
      i++; 
      for(; i<K.num; i++) 
      { 
        p->first=ap; 
        ap->next=NULL; 
        ap->symbol=K.ch[i]; 
        ap->kind=BRANCH; 
        p=ap; 
        ap=(DLTree)malloc(sizeof(DLTNode)); 
      }
      p->first=ap; 
      ap->next=NULL; 
      ap->symbol=Nil; 
      ap->kind=LEAF; 
      ap->infoptr=r; 
      return TRUE;
    }
  }
}
void TraverseDSTable(DLTree p, void(*Visit)(Record*))
{ 
  
  if(p) 
  {
    if(p->kind==BRANCH) 
      TraverseDSTable(p->first, Visit);
    else
      Visit(p->infoptr); 
    TraverseDSTable(p->next, Visit);
  }
}


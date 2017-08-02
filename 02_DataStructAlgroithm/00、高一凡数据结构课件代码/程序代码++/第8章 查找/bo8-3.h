// bo8-3.h 平衡二叉树的基本操作，包括算法9.9～9.12
void R_Rotate(BSTree &p)
{ 
  
  BSTree lc;
  lc=p->lchild; 
  p->lchild=lc->rchild; 
  lc->rchild=p; 
  p=lc; 
}
void L_Rotate(BSTree &p)
{ 
  
  BSTree rc;
  rc=p->rchild; 
  p->rchild=rc->lchild; 
  rc->lchild=p; 
  p=rc; 
}
void LR_Rotate(BSTree &p)
{ 
  BSTree lc=p->lchild; 
  p->lchild=lc->rchild->rchild; 
  lc->rchild->rchild=p; 
  p=lc->rchild; 
  lc->rchild=p->lchild; 
  p->lchild=lc; 
}
void RL_Rotate(BSTree &p)
{ 
  BSTree rc=p->rchild; 
  p->rchild=rc->lchild->lchild; 
  rc->lchild->lchild=p; 
  p=rc->lchild; 
  rc->lchild=p->rchild; 
  p->rchild=rc; 
}
#define LH +1 
#define EH  0 
#define RH -1 
void LeftBalance(BSTree &T) 
{ 
  
  
  
  BSTree lc, rd;
  lc=T->lchild; 
  switch(lc->bf) 
  { case LH: 
             
             T->bf=lc->bf=EH; 
             R_Rotate(T); 
             break;
    case RH: 
             
             rd=lc->rchild; 
             switch(rd->bf)
             { case LH: 
                        T->bf=RH; 
                        lc->bf=EH; 
                        break;
               case EH: 
                        T->bf=lc->bf=EH; 
                        break;
               case RH: 
                        T->bf=EH; 
                        lc->bf=LH; 
             }
             rd->bf=EH; 
#ifndef FLAG 
             L_Rotate(T->lchild);
             
             R_Rotate(T); 
#else 
             LR_Rotate(T); 
#endif
  }
}
void RightBalance(BSTree &T)
{ 
  
  
  
  BSTree rc, ld;
  rc=T->rchild; 
  switch(rc->bf) 
  { case RH: 
             
             T->bf=rc->bf=EH; 
             L_Rotate(T); 
             break;
    case LH: 
             
             ld=rc->lchild; 
             switch(ld->bf)
             { case RH:
                        T->bf=LH; 
                        rc->bf=EH; 
                        break;
               case EH:
                        T->bf=rc->bf=EH; 
                        break;
               case LH:
                        T->bf=EH; 
                        rc->bf=RH; 
             }
             ld->bf=EH; 
#ifndef FLAG 
             R_Rotate(T->rchild);
             
             L_Rotate(T); 
#else 
             RL_Rotate(T); 
#endif
  }
}
Status InsertAVL(BSTree &T, ElemType e, Boolean &taller)
{ 
  
  
  if(T==NULL) 
  { 
    T=(BSTree)malloc(sizeof(BSTNode)); 
    T->data=e; 
    T->lchild=T->rchild=NULL; 
    T->bf=EH; 
    taller=TRUE; 
  }
  else 
  { if EQ(e.key, T->data.key) 
    { 
      return FALSE; 
    }
    if LT(e.key, T->data.key) 
    { if(!InsertAVL(T->lchild, e, taller))
      
        return FALSE; 
      if(taller) 
        switch(T->bf) 
        { case LH: 
                   LeftBalance(T); 
                   taller=FALSE; 
                   break;
          case EH: 
                   T->bf=LH; 
                   taller=TRUE; 
                   break;
          case RH: T->bf=EH; 
                   taller=FALSE; 
        }
    }
    else 
    { if(!InsertAVL(T->rchild, e, taller)) 
        return FALSE; 
      if(taller) 
        switch(T->bf) 
        { case LH: T->bf=EH; 
                   taller=FALSE; 
                   break;
          case EH: 
                   T->bf=RH; 
                   taller=TRUE; 
                   break;
          case RH: 
                   RightBalance(T); 
                   taller=FALSE; 
        }
    }
  }
  return TRUE;
}
void D_LeftBalance(BSTree &p, Boolean &lower) 
{ 
  BSTree ld, rc=p->rchild; 
  switch(rc->bf) 
  { case EH: 
             rc->bf=LH; 
             p->bf=RH;
             L_Rotate(p); 
             lower=FALSE; 
             break;
    case RH: 
             p->bf=rc->bf=EH; 
             L_Rotate(p); 
             lower=TRUE; 
             break;
    case LH: 
             ld=rc->lchild; 
             switch(ld->bf) 
             { case EH: 
                        p->bf=rc->bf=EH; 
                        break;
               case LH: 
                        p->bf=EH; 
                        rc->bf=RH;
                        break;     
               case RH: 
                        p->bf=LH; 
                        rc->bf=EH;
             }
             ld->bf=EH;
#ifndef FLAG 
             R_Rotate(p->rchild); 
             L_Rotate(p); 
#else 
             RL_Rotate(p); 
#endif
             lower=TRUE; 
  }
}
void D_RightBalance(BSTree &p, Boolean &lower) 
{ 
  BSTree rd, lc=p->lchild; 
  switch(lc->bf) 
  { case EH: 
             lc->bf=RH; 
             p->bf=LH;
             R_Rotate(p); 
             lower=FALSE; 
             break;
    case LH: 
             p->bf=lc->bf=EH;
             R_Rotate(p); 
             lower=TRUE; 
             break;
    case RH: 
             rd=lc->rchild; 
             switch(rd->bf) 
             { case EH: 
                        p->bf=lc->bf=EH;
                        break;
               case RH: 
                        p->bf=EH;
                        lc->bf=LH;
                        break;
               case LH: 
                        p->bf=RH;
                        lc->bf=EH;
             }
             rd->bf=EH;
#ifndef FLAG 
             L_Rotate(p->lchild); 
             R_Rotate(p); 
#else 
             LR_Rotate(p); 
#endif
             lower=TRUE; 
  }
}
Status DeleteAVL(BSTree &p, ElemType &e, Boolean &lower) 
{ 
  
  
  BSTree rc, lc;
  ElemType e1;
  if(p==NULL) 
    return FALSE; 
  else 
  { if(EQ(e.key, p->data.key)) 
    { e=p->data; 
      rc=p; 
      if(p->lchild!=NULL && p->rchild!=NULL)
      { 
        if(p->bf==RH) 
        { lc=p->rchild; 
          while(lc->lchild!=NULL) 
            lc=lc->lchild; 
        } 
        else 
        { lc=p->lchild; 
          while(lc->rchild!=NULL) 
            lc=lc->rchild; 
        }
        e1=lc->data; 
        DeleteAVL(p, e1, lower); 
        rc->data=e1; 
      } 
      else 
      { if(p->rchild==NULL) 
          p=p->lchild; 
        else 
          p=p->rchild; 
        delete rc; 
        lower=TRUE; 
      }
    }
    else if(LT(e.key, p->data.key)) 
    { if(!DeleteAVL(p->lchild, e, lower)) 
        return FALSE;
      if(lower) 
      { switch(p->bf) 
        { case EH: 
                   p->bf=RH; 
                   lower=FALSE; 
                   break;
          case LH: 
                   p->bf=EH; 
                   lower=TRUE; 
                   break;
          case RH: 
                   D_LeftBalance(p, lower); 
        }
      }
    }
    else 
    { if(!DeleteAVL(p->rchild, e, lower)) 
        return FALSE;
      if(lower) 
      { switch(p->bf) 
        { case EH: 
                   p->bf=LH; 
                   lower=FALSE; 
                   break;
          case RH: 
                   p->bf=EH; 
                   lower=TRUE; 
                   break;
          case LH: 
                   D_RightBalance(p, lower); 
        }
      }
    }
    return TRUE;
  }
}


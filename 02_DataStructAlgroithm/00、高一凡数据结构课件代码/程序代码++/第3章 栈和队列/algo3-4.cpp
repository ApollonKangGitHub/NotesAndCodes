// algo3-4.cpp 利用栈求解迷宫问题（只输出一个解，算法3.3）
#include"c1.h"
struct PosType 
{ int x; 
  int y; 
};
// 全局变量
PosType begin, end; 
PosType direc[4]={{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
// {行增量, 列增量}，移动方向依次为东南西北
#define MAXLENGTH 25 
typedef int MazeType[MAXLENGTH][MAXLENGTH]; 
MazeType m; 
int x, y; 
void Print()
{ 
  int i, j;
  for(i=0; i<x; i++)
  { for(j=0; j<y; j++)
      printf("%3d", m[i][j]);
    printf("\n");
  }
}
void Init()
{ 
  int i, j, x1, y1;
  printf("请输入迷宫的行数,列数（包括外墙）：");
  scanf("%d,%d", &x, &y);

  for(i=0; i<y; i++) 
  { m[0][i]=0; 
    m[x-1][i]=0; 
  }
  for(i=1; i<x-1; i++)
  { m[i][0]=0; 
    m[i][y-1]=0; 
  }
  for(i=1; i<x-1; i++)
    for(j=1; j<y-1; j++)
      m[i][j]=1; 
  printf("请输入迷宫内墙单元数：");
  scanf("%d", &j);
  printf("请依次输入迷宫内墙每个单元的行数,列数：\n");
  for(i=1; i<=j; i++)
  { scanf("%d,%d", &x1, &y1);
    m[x1][y1]=0; 
  }
  printf("迷宫结构如下：\n");
  Print();
  printf("请输入入口的行数,列数：");
  scanf("%d,%d", &begin.x, &begin.y);
  printf("请输入出口的行数,列数：");
  scanf("%d,%d", &end.x, &end.y);
}
int curstep=1; 
struct SElemType 
{ int ord; 
  PosType seat; 
  int di; 
};
#include"c3-1.h" 
#include"bo3-1.h" 
// 定义墙元素值为0，可通过路径为1，经试探不可通过路径为-1，通过路径为足迹
Status Pass(PosType b)
{ 
  if(m[b.x][b.y]==1)
    return OK;
  else
    return ERROR;
}
void FootPrint(PosType b)
{ 
  m[b.x][b.y]=curstep;
}
void NextPos(PosType &b, int di)
{ 

  b.x+=direc[di].x;
  b.y+=direc[di].y;
}
void MarkPrint(PosType b)
{ 
  m[b.x][b.y]=-1;
}
Status MazePath(PosType start, PosType end) 
{ 
  
  PosType curpos=start; 
  SqStack S; 
  SElemType e; 
  InitStack(S); 
  do
  { if(Pass(curpos)) 
    { FootPrint(curpos); 
      e.ord=curstep; 
      e.seat=curpos; 
      e.di=0; 
      Push(S, e); 
      curstep++; 
      if(curpos.x==end.x && curpos.y==end.y) 
        return TRUE;
      NextPos(curpos, e.di); 
    }
    else 
    { if(!StackEmpty(S)) 
      { Pop(S, e); 
        curstep--; 
        while(e.di==3 && !StackEmpty(S)) 
        { MarkPrint(e.seat); 
          Pop(S, e); 
          curstep--; 
        }
        if(e.di<3) 
        { e.di++; 
          Push(S, e); 
          curstep++; 
          curpos=e.seat; 
          NextPos(curpos,e.di);
        }
      }
    }
  }while(!StackEmpty(S));
  return FALSE;
}
void main()
{
  Init(); 
  if(MazePath(begin, end)) 
  { printf("此迷宫从入口到出口的一条路径如下：\n");
    Print(); 
  }
  else
    printf("此迷宫没有从入口到出口的路径\n");
}


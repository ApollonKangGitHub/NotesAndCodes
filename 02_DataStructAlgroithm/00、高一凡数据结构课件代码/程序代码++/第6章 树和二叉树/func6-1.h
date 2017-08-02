// func6-1.h 利用条件编译，在主程序中选择结点的类型，访问树结点的函数
#include"c1.h"
#if CHAR 
  typedef char TElemType; 
  TElemType Nil='#'; 
  #define form "%c" 
#else 
  typedef int TElemType; 
  TElemType Nil=0; 
  #define form "%d" 
#endif
void visit(TElemType e)
{ printf(form" ", e); 
}


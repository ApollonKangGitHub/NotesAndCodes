// algo7-1.cpp 检验2种结构调用算法7.4～7.6（深度优先和广度优先）搜索遍历的程序
// 如果采用ALGraph类型为图的存储结构，将下行作为注释行
#define MG 
#include"c1.h"
#include"func7-1.h" 
#ifdef MG 
  #include"func7-2.h" 
  #include"c7-1.h" 
  #include"bo7-1.h" 
  typedef MGraph Graph; 
#else 
  #include"func7-4.h" 
  #include"c7-2'.h" 
  #include"bo7-2.h" 
  typedef ALGraph Graph; 
#endif
#include"bo7-3.h" 
void main()
{
  Graph g; 
  char filename[13]; 
  printf("请输入数据文件名：");
  scanf("%s", filename);
 #ifdef MG 
  CreateFromFile(g, filename, 0); 
 #else 
  CreateFromFile(g, filename); 
 #endif
  printf("深度优先搜索遍历的结果：\n");
  DFSTraverse(g, Visit);
  printf("广度优先搜索遍历的结果：\n");
  BFSTraverse(g, Visit);
}


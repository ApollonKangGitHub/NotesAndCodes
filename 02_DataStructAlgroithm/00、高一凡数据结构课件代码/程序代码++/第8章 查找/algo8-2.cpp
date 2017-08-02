// algo8-2.cpp 检验bo8-1.h（有序表部分）的程序
#include"c1.h"
#include"func8-2.h" 
#include"c8-1.h" 
#include"c8-2.h" 
#include"bo8-1.h" 
void main()
{
  SSTable st;
  int i;
  KeyType s;
  Creat_OrdFromFile(st, "f8-2.txt"); 
  printf("有序表为 ");
  Traverse(st, Visit); 
  printf("\n");
  printf("请输入待查找数据的关键字：");
  InputKey(s); 
  i=Search_Bin(st, s);
  
  if(i)
    printf("%d是第%d个数据的关键字\n", st.elem[i].key, i);
  else
    printf("未找到\n");
  Destroy(st); 
}


// algo8-1.cpp 检验bo8-1.h（无序顺序表部分）的程序
#include"c1.h"
#include"func8-1.h" 
#include"c8-1.h" 
#include"c8-2.h" 
#include"bo8-1.h" 
void main()
{
  SSTable st;
  int i;
  long s;
  char filename[13]; 
  printf("请输入数据文件名：");
  scanf("%s", filename);
  Creat_SeqFromFile(st, filename); 
  for(i=1; i<=st.length; i++) 
    st.elem[i].total=st.elem[i].politics+st.elem[i].Chinese+
    st.elem[i].English+st.elem[i].math+st.elem[i].physics+
    st.elem[i].chemistry+st.elem[i].biology;
  printf("准考证号  姓名    政治 语文 外语 数学 物理 化学 生物 总分\n");
  Traverse(st, Visit); 
  printf("请输入待查找人的考号：");
  InputKey(s); 
  i=Search_Seq(st, s); 
  if(i) 
    Visit(st.elem[i]); 
  else
    printf("未找到\n");
  Destroy(st); 
}


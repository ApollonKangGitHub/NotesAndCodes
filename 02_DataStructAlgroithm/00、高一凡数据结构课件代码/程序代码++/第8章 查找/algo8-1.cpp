// algo8-1.cpp ����bo8-1.h������˳����֣��ĳ���
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
  printf("�����������ļ�����");
  scanf("%s", filename);
  Creat_SeqFromFile(st, filename); 
  for(i=1; i<=st.length; i++) 
    st.elem[i].total=st.elem[i].politics+st.elem[i].Chinese+
    st.elem[i].English+st.elem[i].math+st.elem[i].physics+
    st.elem[i].chemistry+st.elem[i].biology;
  printf("׼��֤��  ����    ���� ���� ���� ��ѧ ���� ��ѧ ���� �ܷ�\n");
  Traverse(st, Visit); 
  printf("������������˵Ŀ��ţ�");
  InputKey(s); 
  i=Search_Seq(st, s); 
  if(i) 
    Visit(st.elem[i]); 
  else
    printf("δ�ҵ�\n");
  Destroy(st); 
}


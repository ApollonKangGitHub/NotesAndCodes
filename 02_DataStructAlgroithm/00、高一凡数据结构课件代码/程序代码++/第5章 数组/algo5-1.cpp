// algo5-1.cpp �䳤������������ʵ�θ����ɱ䣩���ʾ��
#include"c1.h"
typedef int ElemType; 
ElemType Max(int num, ...) 
{ 
  va_list ap; 
  int i;
  ElemType m, n;
  if(num<1)
    exit(OVERFLOW);

  va_start(ap, num); 
  m=va_arg(ap, ElemType); 
  for(i=1; i<num; i++) 
  { n=va_arg(ap, ElemType); 
    if(m<n)
      m=n; 
  }
  va_end(ap); 
  return m; 
}
void main()
{
  printf("1.���ֵΪ%d\n", Max(4, 7, 9, 5, 8)); 
  printf("2.���ֵΪ%d\n", Max(3, 17, 36, 25)); 
}


// func5-2.h ϡ��������������main5-2.cpp��main5-3.cpp����
void main()
{
  TSMatrix A, B, C;
  printf("��������A��");
  CreateSMatrix(A); 
  PrintSMatrix(A); 
  CopySMatrix(A, B); 
  printf("�ɾ���A���ƾ���B��\n");
  PrintSMatrix(B); 
  DestroySMatrix(B); 
  printf("���پ���B��\n");
  PrintSMatrix(B); 
  printf("��������B2���������A���С�������ͬ���С��зֱ�Ϊ%d��%d��\n", A.mu, A.nu);
  CreateSMatrix(B); 
  PrintSMatrix(B); 
  AddSMatrix(A, B, C); 
  printf("����C1��A+B����\n");
  PrintSMatrix(C); 
  SubtSMatrix(A, B, C); 
  printf("����C2��A-B����\n");
  PrintSMatrix(C); 
  TransposeSMatrix(A, C); 
  printf("����C3��A��ת�ã���\n");
  PrintSMatrix(C); 
  printf("��������A2��");
  CreateSMatrix(A); 
  PrintSMatrix(A); 
  printf("��������B3��������Ӧ�����A2��������ͬ=%d��\n", A.nu);
  CreateSMatrix(B); 
  PrintSMatrix(B); 
#ifndef FLAG 
  MultSMatrix(A, B, C); 
#else 
  MultSMatrix1(A, B, C); 
#endif
  printf("����C5��A��B����\n");
  PrintSMatrix(C); 
}


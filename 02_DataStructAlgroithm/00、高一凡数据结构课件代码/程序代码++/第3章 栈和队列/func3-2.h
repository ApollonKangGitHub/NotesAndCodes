// func3-2.h �����е���������main3-2.cpp��main3-3.cpp����
void main()
{
  int i;
  QElemType d;
  LinkQueue q;
  InitQueue(q); 
  printf("�ɹ��ع�����һ���ն���\n");
  printf("�Ƿ�ն��У�%d��1���� 0���񣩣�", QueueEmpty(q));
  printf("���еĳ���Ϊ%d\n", QueueLength(q));
  EnQueue(q, -5); 
  EnQueue(q, 5);
  EnQueue(q, 10);
  printf("����3��Ԫ�أ�-5��5��10���󣬶��еĳ���Ϊ%d\n", QueueLength(q));
  printf("�Ƿ�ն��У�%d��1���� 0���񣩣�", QueueEmpty(q));
  printf("���е�Ԫ������Ϊ");
  QueueTraverse(q, print); 
  i=GetHead(q, d); 
  if(i==OK) 
    printf("��ͷԪ����%d��", d);
  DeQueue(q, d); 
  printf("ɾ���˶�ͷԪ��%d��", d);
  i=GetHead(q, d); 
  if(i==OK) 
    printf("�µĶ�ͷԪ����%d\n", d);
  ClearQueue(q); 
  printf("��ն��к�q.front=%u��q.rear=%u��q.front->next=%u\n", q.front,
  q.rear, q.front->next);
  DestroyQueue(q); 
  printf("���ٶ��к�q.front=%u��q.rear=%u\n", q.front, q.rear);
}


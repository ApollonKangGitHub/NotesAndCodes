// c3-2.h �������У����е���ʽ�洢�ṹ���������61ҳ
typedef struct QNode
{ QElemType data;
  QNode *next;
}*QueuePtr;
struct LinkQueue
{ QueuePtr front, rear; 
};


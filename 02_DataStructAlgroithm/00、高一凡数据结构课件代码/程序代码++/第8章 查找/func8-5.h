// func8-5.h ��������Ԫ�����͵Ķ��弰�����Ĳ���
typedef int KeyType; 
struct ElemType 
{ KeyType key; 
  int others; 
};
void Visit(ElemType c) 
{ printf("(%d,%d)", c.key, c.others);
}
void InputFromFile(FILE* f, ElemType &c) 
{ fscanf(f, "%d%d", &c.key, &c.others);
}
void InputKey(KeyType &k) 
{ scanf("%d", &k);
}


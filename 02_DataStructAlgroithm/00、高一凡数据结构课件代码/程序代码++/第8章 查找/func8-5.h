// func8-5.h 包括数据元素类型的定义及对它的操作
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


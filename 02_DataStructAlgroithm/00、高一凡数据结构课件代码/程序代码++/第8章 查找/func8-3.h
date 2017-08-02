// func8-3.h 包括数据元素类型的定义及对它的操作
typedef char KeyType; 
struct ElemType 
{ KeyType key; 
  int weight; 
};
void Visit(ElemType c) 
{ printf("(%c,%d)", c.key, c.weight);
}
void InputFromFile(FILE* f, ElemType &c) 
{ fscanf(f, "%*c%c %d", &c.key, &c.weight); 
}
void InputKey(KeyType &k) 
{ scanf("%c", &k);
}


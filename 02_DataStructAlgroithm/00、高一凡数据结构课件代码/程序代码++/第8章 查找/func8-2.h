// func8-2.h 包括数据元素类型的定义及对它的操作
typedef int KeyType; 
struct ElemType 
{ KeyType key; 
};
void Visit(ElemType c) 
{ printf("%d ", c.key);
}
void InputFromFile(FILE* f, ElemType &c) 
{ fscanf(f, "%d", &c.key);
}
void InputKey(KeyType &k) 
{ scanf("%d", &k);
}


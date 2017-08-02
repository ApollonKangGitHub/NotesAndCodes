// func8-7.h 包括对键树的输入输出操作
void Visit(Record* r) 
{ printf("(%s,%d)", r->key.ch, r->others.order);
}
void InputKey(char* k) 
{ scanf("%s", k); 
}


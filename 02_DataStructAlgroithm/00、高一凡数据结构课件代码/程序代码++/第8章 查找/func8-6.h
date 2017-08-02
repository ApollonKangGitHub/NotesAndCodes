// func8-6.h 包括对B_树的输入输出操作
void Visit(BTNode c, int i) 
{ printf("(%d,%d)", c.recptr[i]->key, c.recptr[i]->others.order);
}
void InputKey(KeyType &k) 
{ scanf("%d", &k);
}


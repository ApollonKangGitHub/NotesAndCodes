// func7-1.h 包括顶点信息类型的定义及对它的操作
#define MAX_NAME 9 
struct VertexType
{ char name[MAX_NAME]; 
};
void Visit(VertexType ver)
{ printf("%s ", ver.name);
}
void Input(VertexType &ver)
// 与之配套的输入顶点信息的函数
{ scanf("%s", ver.name);
}
void InputFromFile(FILE* f, VertexType &ver)
// 与之配套的从文件输入顶点信息的函数
{ fscanf(f, "%s", ver.name);
}


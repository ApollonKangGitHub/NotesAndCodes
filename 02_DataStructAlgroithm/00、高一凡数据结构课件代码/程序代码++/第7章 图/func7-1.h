// func7-1.h ����������Ϣ���͵Ķ��弰�����Ĳ���
#define MAX_NAME 9 
struct VertexType
{ char name[MAX_NAME]; 
};
void Visit(VertexType ver)
{ printf("%s ", ver.name);
}
void Input(VertexType &ver)
// ��֮���׵����붥����Ϣ�ĺ���
{ scanf("%s", ver.name);
}
void InputFromFile(FILE* f, VertexType &ver)
// ��֮���׵Ĵ��ļ����붥����Ϣ�ĺ���
{ fscanf(f, "%s", ver.name);
}


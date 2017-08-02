// c9-3.h 静态链表类型。在严书第268页
#define SIZE 100 
struct SLNode 
{ RedType rc; 
  int next; 
};
struct SLinkListType 
{ SLNode r[SIZE]; 
  int length; 
};


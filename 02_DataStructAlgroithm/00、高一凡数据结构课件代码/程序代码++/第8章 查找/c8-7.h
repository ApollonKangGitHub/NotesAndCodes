// c8-7.h 键树记录的存储结构。在严书第248页
#define MAX_KEY_LEN 16 
struct KeyType 
{ char ch[MAX_KEY_LEN]; 
  int num; 
};
enum NodeKind{LEAF, BRANCH}; 


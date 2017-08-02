// c8-11.h 开放定址哈希表的存储结构。在严书第259页
int hashsize[]={11, 19, 29, 37}; 
struct HashTable
{ ElemType *elem; 
  int count; 
  int sizeindex; 
};
#define SUCCESS 1
#define UNSUCCESS 0
#define DUPLICATE -1


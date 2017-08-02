// c8-10.h 对两个字符串型关键字的比较约定为如下的宏定义。在严书第215页
#define EQ(a, b) (!strcmp((a), (b)))
#define LT(a, b) (strcmp((a), (b))<0)
#define LQ(a, b) (strcmp((a), (b))<=0)


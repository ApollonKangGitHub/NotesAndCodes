// c1.h （文件名）
#include<string.h> 
#include<ctype.h> 
#include<malloc.h> 
#include<limits.h> 
#include<stdio.h> 
#include<stdlib.h> 
#include<io.h> 
#include<math.h> 
#include<sys/timeb.h> 
#include<stdarg.h> 
// 函数结果状态代码。在严书第10页
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
// #define INFEASIBLE -1 没使用
// #define OVERFLOW -2 因为在math.h中已定义OVERFLOW的值为3，故去掉此行
typedef int Status; 
typedef int Boolean; 


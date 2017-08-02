#ifndef _BIT_H
#define _BIT_H

//进行位运算操作的函数
//获取指定地址指定位信息（0/1）
int get_bit(unsigned char *, int);

//设置指定地址指定位信息（value = 0/1）
void set_bit(unsigned char *, int, int);

//异或操作,output存储异或后的结果，size为需要异或的位数
void xor_bit(unsigned char *, unsigned char *, unsigned char *, int);

//循环左移，size为总循环的长度，num为循环左移的位数
void rol_bit(unsigned char *, int, int);

#endif 

#ifndef _SHA1_H
#define _SHA1_H

#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <assert.h>
#include <stdlib.h>

#define uint8 unsigned char
//#define uint32 unsigned int
#define uint32 unsigned long int
#define KEY1 0X5A827999
#define KEY2 0X6ED9EBA1
#define KEY3 0X8F1BBCDC
#define KEY4 0XCA62C1D6

typedef struct sha_message{
	uint32 length[2];//简单起见，只用length[0]，只影响能够加密的文件大小上限
	uint32 buffer[5];//A、B、C、D、E状态
//    uint8 message[64];//64*8=512bit的message
}ShaMess;

void ShaAlgorithm(const char *);
void ShaGetCiphertext(ShaMess *, unsigned char *);
//结构体初始化
void ShaInit(ShaMess *, uint32);
void ShaPadding(ShaMess *, unsigned char *, int);
//进行散列值的基萨u年
void ShaCalcHashValue(ShaMess *, unsigned char *);
//对512bit的信息进行分组计算W
void ShaCalcW(uint32 *, unsigned char *);
//4个8bit的信息，拼接成1个32bit的信息
void get_uint32(uint32 *, void *, int);
//1个32bit的信息，分解为4个8bit的信息
void put_uint32(uint32 *, void *, int);
//循环左移
uint32 LoopLeftMove(uint32, int);
#endif // _SHA_H

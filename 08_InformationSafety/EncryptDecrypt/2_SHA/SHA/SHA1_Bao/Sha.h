#ifndef _SHA_H
#define _SHA_H

#include"StdAfx.h"
 
#define uint8  unsigned char 
#define uint32 unsigned long int 
 
struct sha1_context 
{                    //0处理的数据长度  1未处理的数据长度
    uint32 total[2]; //记录信息的长度信息 一共8个字节 64位
    uint32 state[5]; 
    uint8 buffer[64]; 
}; 
 
void sha1_starts( struct sha1_context *ctx ); 
void sha1_update( struct sha1_context *ctx, uint8 *input, uint32 length ); 
void sha1_finish( struct sha1_context *ctx, uint8 digest[20] ); 

//////////////////////////////////////////////////////////
void show_ciphertext(unsigned char ciphertext[20]);
void Sha();

#endif

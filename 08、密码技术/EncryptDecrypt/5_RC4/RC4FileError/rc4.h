#ifndef _RC4_H
#define _RC4_H

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#define BUFSIZE 65535

void rc4_algorithm(unsigned char *, unsigned char *);
//初始化S盒
void vector_init(unsigned char *, unsigned char *, unsigned int);
//加密（解密同流程）：P ^ K = C,C ^ K = P
void encrypt(unsigned char *,unsigned char *, unsigned int);
void swap(unsigned char *, unsigned char *);


#endif

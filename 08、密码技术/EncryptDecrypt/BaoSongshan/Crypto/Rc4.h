#ifndef _RC4_H
#define _RC4_H

#include"StdAfx.h"

void swap(unsigned char *x, unsigned char *y);
void rc4_init(unsigned char S[256], unsigned char*key, int key_len);
void rc4_crypt(unsigned char S[256], unsigned char *data,int data_len);

void Rc4();

#endif
#ifndef _BIT_H
#define _BIT_H

#include"StdAfx.h"

//  00101010  bit_get(x,2)
//            bit_set(x,1,0);
//            bit_rot_left(x,8,3)

int bit_get(const unsigned char *bits, 
			int pos);

void bit_set(unsigned char *bits, int pos, 
			 int state);

void bit_xor(const unsigned char *bits1, 
			 const unsigned char *bits2, 
			 unsigned  char *bitsx, 
			 int size);

void bit_rot_left(unsigned char *bits, 
				  int size, 
				  int count);

#endif
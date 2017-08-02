#ifndef _MD5_H
#define _MD5_H

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char uint8;
typedef unsigned long uint32;

typedef struct md5_struct{
	uint32 state[8];//存放散列值
	uint32 length[2];//用length[0]存放
}MD5STR;

void md5_algroithm(char const *);
void md5_showHashValue(MD5STR *);
void md5_init(MD5STR *, uint32);
void md5_padding(MD5STR *, unsigned char *, uint32);
void md5_calcHashValue(MD5STR * md5, unsigned char * data);
void calcM(uint32 * m, unsigned char * data);
void FirstRound(uint32 &, uint32, uint32, uint32, uint32, uint8, uint32);
void SecondRound(uint32 &, uint32, uint32, uint32, uint32, uint8, uint32);
void ThirdRound(uint32 &, uint32, uint32, uint32, uint32, uint8, uint32);
void LastRound(uint32 &, uint32, uint32, uint32, uint32, uint8, uint32);

#endif

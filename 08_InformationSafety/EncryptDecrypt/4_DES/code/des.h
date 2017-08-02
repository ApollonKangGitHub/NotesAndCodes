#ifndef _DES_H
#define _DES_H

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

typedef enum operation_type{ENCRYPT, DECRYPT}OperType;//加密、解密

void des(OperType, char *, char *, char *);
void get_KeyAndVector(unsigned char * , unsigned char *, OperType, char *);
static void des_AlgorithmDeal(unsigned char [], unsigned char [], OperType);
static void permute(unsigned char *, const int *, int);
#endif

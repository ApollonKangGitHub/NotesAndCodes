#ifndef _PRIME_H
#define _PRIME_H

#include"StdAfx.h"

typedef unsigned long UL;

typedef __int64 lltype;
const int MAX_COUNT = 20;//≤‚ ‘¥Œ ˝

//back = (a*b)%num      ( n <= 2^62)
lltype fMultiModular(const lltype &a, lltype b, const lltype &n);

lltype modular_exp(const lltype &a, lltype b, const lltype &n);

bool fWitNess(const lltype &a, const lltype &n, char t, const lltype &u);

bool miller_rabin(const lltype &n, int count); 


bool TestPrime(UL value);
void Prime(int num);

#endif
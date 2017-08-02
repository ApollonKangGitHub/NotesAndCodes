#ifndef _RSA_H
#define _RSA_H

#include"StdAfx.h"
typedef unsigned long Huge;

typedef struct RsaPK
{
	Huge e;
	Huge n;
} RsaPK;
typedef struct RsaSK
{
	Huge d;
	Huge n;
}RsaSK;

void RandomE(Huge f,Huge &e);
Huge Inverses(Huge n, Huge e);
Huge ModExp(Huge a, Huge b, Huge n);

void PK(RsaPK *pk, Huge p, Huge q);
void SK(RsaSK *sk, Huge e, Huge p, Huge q);
void RsaEncrypt(Huge plaintext, Huge *ciphertext, RsaPK *pk);
void RsaDecrypt(Huge ciphertext, Huge *plaintext, RsaSK *sk);
void Rsa();

#endif
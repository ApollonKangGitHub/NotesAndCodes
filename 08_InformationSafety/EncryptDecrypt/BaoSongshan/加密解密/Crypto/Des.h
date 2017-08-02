#ifndef _DES_H
#define _DES_H

#include"StdAfx.h"

void des_encipher(const unsigned char *plaintext, 
				  unsigned char *ciphertext,
				  const unsigned char *key);

void des_decipher(const unsigned char *ciphertext, 
				  unsigned char *plaintext,
				  const unsigned char *key);

void cbc_encipher(const unsigned char *plaintext,
				  unsigned char *ciphertext,
				  const unsigned char *key,
				  int size);

void cbc_decipher(const unsigned char *ciphertext,
				  unsigned char *plaintext,
				  const unsigned char *key,
				  int size);

void Des();

void Cbc_Des();

#endif
#ifndef _COMMON_H
#define _COMMON_H

#include <stdio.h>

void sort(char**, int);
void transpose(int (*)[3], int (*)[2]);

void trans_call(void (*)(int (*)[3], int (*)[2]),  int (*)[3],  int (*)[2]);
void sort_call(void (*)(char**, int),  char** , int );


#endif	/* common.h  */

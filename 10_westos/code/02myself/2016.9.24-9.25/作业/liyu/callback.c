#include "common.h"
void graaa(void (*ptrans)(int (*)[4],int n),int (*pa)[4],int n)
{
	ptrans(pa,5);
}
void maa(void (*pt)(int (*)[4],int n),int (*pa)[4],int n)
{
	pt(pa,5);
}

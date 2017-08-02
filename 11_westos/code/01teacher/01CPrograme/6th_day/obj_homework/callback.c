#include "common.h"

void trans_call(void (*ptrans)(int (*)[3], int (*)[2]),  int (*pa)[3],  int (*pb)[2])
{
	ptrans(pa, pb);
}

void sort_call(void (*psort)(char**, int),  char** ps, int len)
{
	psort(ps, len);
}




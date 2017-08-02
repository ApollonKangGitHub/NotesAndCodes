#include "sha1.h"

int main(int argc, char * argv[])
{
#if 0
	if(argc != 2){
		printf("Format:%s plaintextFileName\n",argv[0]);
		return 0;
	}
#endif
    ShaAlgorithm(argv[1]);
    return 0;
}

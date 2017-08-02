#include "md5.h"

int main(int argc, char * argv[])
{
	if(argc != 2){
		printf("Fromat:%s inputFileName\n",argv[0]);
		return -1;
	}

	md5_algroithm(argv[1]);

	return 0;
}

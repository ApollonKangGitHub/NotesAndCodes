#include "des.h"

int main(int argc, char * argv[])
{
	if(argc != 5){
		printf("format:%s -e plaintextFileName ciphertextFileName keyFileName\n",argv[0]);
		printf("format:%s -d ciphertextFileName plaintextFileName keyFileName\n",argv[0]);
		exit(EXIT_FAILURE);
	}
	if(!strcmp(argv[1], "-e")){
		des(ENCRYPT,argv[2],argv[3],argv[4]);
	}
	else if(!strcmp(argv[1], "-d")){
		des(DECRYPT,argv[2],argv[3],argv[4]);
	}
	else{	
		printf("format:%s -e plaintextFileName ciphertextFileName keyFileName\n",argv[0]);
		printf("format:%s -d ciphertextFileName plaintextFileName keyFileName\n",argv[0]);
		exit(EXIT_FAILURE);
	}
	return 0;
}

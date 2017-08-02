#include "rc4.h"

int main(int argc, char * argv[])
{	
	if(argc != 4){
		printf("Format:%s keyString inputFile outputFile\n",argv[0]);
		printf("Format:%s keyString inputFile outputFile\n",argv[0]);
		return 0;
	}

	unsigned char message[BUFSIZE] = {0};

	FILE *fpin = fopen(argv[2],"r");
	assert(NULL != fpin);
	FILE *fpout = fopen(argv[3],"w");
	assert(NULL != fpout);

	while(feof(fpin)){
		fread(message, sizeof(message), 1, fpin);
	}
	printf("size = %d\n",sizeof(message));
	rc4_algorithm(message, (unsigned char *)argv[1]);//message and key
	fwrite(message, strlen((const char *)message), 1, fpout);

	int len = strlen((const char *)message);
	for(int i = 0; i<len; i++){
		printf("%02x",message[i]);
	}

	printf("\nlen = %d\n",len);
	fclose(fpin);
	fclose(fpout);

	return 0;
}

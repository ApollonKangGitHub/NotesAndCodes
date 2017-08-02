#include<multiproccp.h>

int main(int argc, char ** argv)
{
	if(argc != 3){
		printf("The parameter is too little or lot!\n");
		printf("example: <mpcp oldbigfile newbigfile N>(N is the num of process)\n");
		exit(EXIT_FAILURE);
	}

	deal_multi_process_copy(argv[1], argv[2]);

	return 0;
}

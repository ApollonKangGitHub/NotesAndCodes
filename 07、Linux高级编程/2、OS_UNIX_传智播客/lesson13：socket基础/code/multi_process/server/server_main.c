#include<multiproc.h>

int main(char argc, char **argv)
{
	if(argc < 3 ){
                printf("Too few parameter!\n");
		exit(EXIT_FAILURE);
	}

	socket_server_create(argv[1], argv[2]);
	return 0;
}

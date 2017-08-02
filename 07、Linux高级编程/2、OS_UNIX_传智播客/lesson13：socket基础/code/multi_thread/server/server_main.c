#include<multithread.h>
#include<server.h>

int main(int argc, char **argv)
{
	if(argc < 3 ){
		printf("Too few parameter!\n");
		exit(EXIT_FAILURE);
	}

	socket_server_create(argv[1], argv[2]);
	return 0;
}

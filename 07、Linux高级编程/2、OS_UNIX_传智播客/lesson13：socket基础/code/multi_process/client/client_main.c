#include<multiproc.h>
#include<client.h>

int main(char argc, char ** argv)
{
	if(argc < 3){
                printf("Too few parameter!\n");
		exit(EXIT_FAILURE);
	}
	socket_client_create(argv[1], argv[2]);
}

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<arpa/inet.h>
#include<netinet/in.h>

int main(char argc, char ** argv)
{
	struct sockaddr_in seraddr;
	int confd;
	char ipbuf[] = "127.0.0.1";
	confd = socket(AF_INET, SOCK_DGRAM, 0);

	bzero(&seraddr, sizeof(seraddr));
	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(atoi(argv[1]));
//	seraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	inet_pton(AF_INET, ipbuf, &seraddr.sin_addr.s_addr);

	char buf[20] = "hello server!\n";
	int ret = sendto(confd, buf, strlen(buf), 0,
					(struct sockaddr *)&seraddr, sizeof(seraddr));
	if(ret < 0){
		perror("write");
		exit(EXIT_FAILURE);
	}
	close(confd);

	return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<arpa/inet.h>
#include<netinet/in.h>

#define MAXLINE 1500//当前MTU

int main(char argc, char ** argv)
{
	if(argc < 2){
		printf("two few parameter!\n");
		exit(EXIT_FAILURE);
	}

	char buf[MAXLINE] = {};
	char ipaddr[INET_ADDRSTRLEN] = {};/*INET_ADDRSTRLEN为16个字节*/
	
	struct sockaddr_in seraddr, cliaddr;
	int sockfd, len;
	socklen_t addrlen;
	
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	bzero(&seraddr, sizeof(seraddr));
	seraddr.sin_family = AF_INET;
//	seraddr.sin_addr.s_addr = htonl(INADDR_ANY);//本地任意IP
	seraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	seraddr.sin_port = htons(atoi(argv[1]));

	//printf("INADDR_ANY = %x\n", INADDR_ANY);

	bind(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr));
	
	while(1){	
		bzero(buf,sizeof(buf));
		addrlen = sizeof(cliaddr);
		
		len = recvfrom(sockfd, buf, sizeof(buf), 0,
					(struct sockaddr *)&cliaddr, &addrlen);
		inet_ntop(AF_INET, &cliaddr.sin_addr.s_addr,ipaddr,sizeof(ipaddr));
		printf("%s\t%d\n", ipaddr, ntohs(cliaddr.sin_port));

		write(STDOUT_FILENO, buf, len);
	}
	close(sockfd);
	return 0;
}

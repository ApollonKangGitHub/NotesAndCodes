#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>

#define _PORT_ 8080

int main()
{
	int sock = socket(AF_INET,SOCK_DGRAM,0);
	if(sock < 0)
	{
		perror("socket");
		exit(1);
	}

	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(_PORT_);
	local.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind(sock,(struct sockaddr*)&local,sizeof(local)) < 0)
	{
		perror("bind");
		exit(1);
	}
	
	struct sockaddr_in client; //output val
	socklen_t len = sizeof(client); //output val
	char buf[1024];
	memset(buf,'\0',sizeof(buf));
	while(1)
	{
		ssize_t _size = recvfrom(sock,buf,sizeof(buf) - 1,0,\
					(struct sockaddr*)&client,&len);
		if(_size < 0)
		{
			//perror("recvfrom");
			printf("0\n");
			continue;
		}
		else if(_size > 0)
		{
			buf[_size] = '\0';
			printf("client -> %s",buf);
			//Data sent back to the client
			//ssize_t sendto(int sockfd, const void *buf, size_t len,\
			//int flags,const struct sockaddr *dest_addr, socklen_t addrlen)
			ssize_t echo_size = sendto(sock,buf,strlen(buf), \
						0,(struct sockaddr*)&client,len);
			if(echo_size < 0)
			{
				perror("sendto");
				break;
			}
		}
		else
		{
			printf("data sent over\n");
			break;
		}
		
	}
	
	return 0;
}

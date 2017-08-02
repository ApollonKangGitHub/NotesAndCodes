#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<netinet/in.h>

#define _PORT_ 8080

int main()
{
	int sock = socket(AF_INET,SOCK_DGRAM,0);
	if(sock < 0)
	{
		perror("socket");
		exit(1);
	}

	char buf[1024];
	memset(buf,'\0',sizeof(buf));

        struct sockaddr_in remote;
	remote.sin_family = AF_INET;
	remote.sin_port = htons(_PORT_);
	remote.sin_addr.s_addr = htonl(INADDR_ANY);
	socklen_t len = sizeof(remote); //output val

	while(1)
	{
		ssize_t _size = read (0,buf,sizeof(buf) - 1);
		if(_size < 0)
		{
			perror("recvfrom");
			break;
		}
		else if(_size > 0)
		{
			buf[_size] = '\0';
			//ssize_t sendto(int sockfd, const void *buf, size_t len,\
			//int flags,const struct sockaddr *dest_addr, socklen_t addrlen)
			ssize_t sent_size = sendto(sock,buf,strlen(buf),0,(struct sockaddr*)&remote,len);
			if(sent_size < 0)
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
		
		memset(buf,'\0',sizeof(buf));
		ssize_t echo_size = recvfrom(sock,buf,sizeof(buf) - 1,0,(struct sockaddr*)&remote,&len);
		if(echo_size < 0)
		{
			perror("recvfrom");
			break;
		}
		else
		{
			buf[echo_size] = '\0';
			printf("echo -> %s",buf);
		}
	}
	
	return 0;
}

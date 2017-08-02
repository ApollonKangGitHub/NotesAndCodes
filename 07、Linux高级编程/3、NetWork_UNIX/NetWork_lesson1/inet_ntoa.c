#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdlib.h>
int main(void)
{
	struct in_addr ipaddr;
	bzero(&ipaddr,sizeof(ipaddr));
#if 1
	int point = inet_aton("192.128.127.127",&ipaddr);
	if(point == 0){
		printf("Change Failure!\n");
		exit(EXIT_FAILURE);
	}
#endif
#if 0
	unsigned long addr = inet_addr("192.128.127.127");
	ipaddr.s_addr = addr;
#endif
	printf("IP_ADDRESS_BINARY:%X\n",ipaddr);//输出是大端模式
	printf("IP_ADDRESS_STRING:%s\n",inet_ntoa(ipaddr));//输出是小端模式

	return 0;
}

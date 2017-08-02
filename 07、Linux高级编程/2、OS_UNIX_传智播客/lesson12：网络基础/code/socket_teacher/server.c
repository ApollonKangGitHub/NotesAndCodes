#include <sys/types.h>      
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>

#define SERVER_PORT 8000
#define MAXLINE 4096
int main(void)
{
    struct sockaddr_in serveraddr, clientaddr;
    int sockfd, addrlen, confd, len, i;
    char ipstr[128];
    char buf[MAXLINE];

    //1.socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    //2.bind
    bzero(&serveraddr, sizeof(serveraddr));
    /* 地址族协议IPv4 */
    serveraddr.sin_family = AF_INET;
    /* IP地址 */
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(SERVER_PORT);
    bind(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    //3.listen
    listen(sockfd, 128);
    while (1) {
        //4.accept阻塞监听客户端链接请求
        addrlen = sizeof(clientaddr);
        confd = accept(sockfd, (struct sockaddr *)&clientaddr, &addrlen);
        //输出客户端IP地址和端口号
        inet_ntop(AF_INET, &clientaddr.sin_addr.s_addr, ipstr, sizeof(ipstr));
        printf("client ip %s\tport %d\n", 
                inet_ntop(AF_INET, &clientaddr.sin_addr.s_addr, ipstr, sizeof(ipstr)),
                ntohs(clientaddr.sin_port));

        //和客户端交互数据操作confd
        //5.处理客户端请求 
        len = read(confd, buf, sizeof(buf));
        i = 0;
        while (i < len) {
            buf[i] = toupper(buf[i]);
            i++;
        }
        write(confd, buf, len);

        close(confd);
    }
    close(sockfd);

    return 0;
}

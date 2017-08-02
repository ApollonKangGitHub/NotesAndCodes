/*************************************************************************
	> File Name: client.c
	> Author: 
	> Mail: 
	> Created Time: 一 11/21 09:24:04 2016
 ************************************************************************/

#include<stdio.h>

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#define MAXBUF 1024
int main(int argc, char **argv)
{
    int sockfd, len;
    pid_t pd;
    struct sockaddr_in dest;
    char buffer[MAXBUF + 1];
    fd_set rfds;
    struct timeval tv;
    int retval, maxfd = -1;
    if (argc != 3) {
        printf("Usage: %s IP port\n",argv[0]);
        exit(0);
    }
   
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket");
        exit(errno);
    }
   
    bzero(&dest, sizeof(dest));
    dest.sin_family = AF_INET;
    dest.sin_port = htons(atoi(argv[2]));
    if (inet_aton(argv[1], (struct in_addr *) &dest.sin_addr.s_addr) == 0) {
        perror(argv[1]);
        exit(errno);
    }
   
    if (connect(sockfd, (struct sockaddr *) &dest, sizeof(dest)) != 0) {
        perror("Connect ");
        exit(errno);
    }
    printf("\nConnecting to Sever .......OK\n");
    while (1) {
       
        FD_ZERO(&rfds);
       
        FD_SET(0, &rfds);
        maxfd = 0;
       
        FD_SET(sockfd, &rfds);
        if (sockfd > maxfd)
            maxfd = sockfd;
       
        tv.tv_sec = 1;
        tv.tv_usec = 0;
       
        retval = select(maxfd + 1, &rfds, NULL, NULL, &tv);
        if (retval == -1) {
            printf("#ERR: select error %s", strerror(errno));
            break;
        } else if (retval == 0) {
            continue;
        } else {
            if (FD_ISSET(sockfd, &rfds)) {
               
                bzero(buffer, MAXBUF + 1);
               
                len = recv(sockfd, buffer, MAXBUF, 0);
                if (len > 0)
                    printf("Sever: %s(%d)\n",buffer, len);
                else {
                    if (len < 0)
                        printf("#ERR: error %d, %s'\n",errno, strerror(errno));
                    else
                        printf("#ERR: Server disconnect！\n");
                    break;
                }
            }

            if (FD_ISSET(0, &rfds)) {
               
                bzero(buffer, MAXBUF + 1);
                fgets(buffer, MAXBUF, stdin);
                if (!strncasecmp(buffer, "quit", 4)) {
                    printf("#INFO: Exit！\n");
                    break;
                }
               
                len = send(sockfd, buffer, strlen(buffer) - 1, 0);
                if (len < 0) {
                    printf("#ERR: Send msg %s,error %d, %s\n",
                                buffer, errno, strerror(errno));
                    break;
                }
            }
        }
   }
    close(sockfd);
    return 0;
}   

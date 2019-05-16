/*************************************************************************
	> File Name: server.c
	> Author: 
	> Mail: 
	> Created Time: 一 11/25 21:23:35 2016
 ************************************************************************/

#include<stdio.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <sys/types.h>
#include <fcntl.h>

#define MAXBUF 1024

int main(int argc, char **argv)
{
    int sockfd, new_fd, reuse;
    socklen_t len;
    struct sockaddr_in my_addr, their_addr;
    unsigned int myport, lisnum;
    char buf[MAXBUF + 1];
    fd_set rfds;
    struct timeval tv;
    int retval, maxfd = -1;
   

    if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket\n");
        exit(1);
    }
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse))< 0) {
        perror("setsockopt error\n");
        return -1;
    }

    bzero(&my_addr, sizeof(my_addr));
    my_addr.sin_family = PF_INET;
    my_addr.sin_port = htons(8888);
    my_addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(sockfd, (struct sockaddr *) &my_addr, sizeof(struct sockaddr)) == -1) {
        perror("bind\n");
        exit(1);
    }

    if (listen(sockfd, lisnum) == -1) {
        perror("listen\n");
        exit(1);
    }

    while (1) {
        printf("\nWaiting for clint connect....\n");
        len = sizeof(struct sockaddr);
        if ((new_fd = accept(sockfd, (struct sockaddr *) &their_addr,&len)) == -1) {
            perror("accept");
            exit(errno);
        } else
            printf("server: got connection from %s, port %d, socket %d\n",
                   inet_ntoa(their_addr.sin_addr),ntohs(their_addr.sin_port), new_fd);
       
    #if 0
    int status = fcntl(new_fd, F_SETFL, fcntl(sockfd, F_GETFL, 0) | O_NONBLOCK);

    if (status == -1){
        perror("calling fcntl");
    }
    #endif 

        printf("\nconnecting ......OK\n");
        while (1) {
            FD_ZERO(&rfds);
            FD_SET(0, &rfds);
            maxfd = 0;
            FD_SET(new_fd, &rfds);
            if (new_fd > maxfd)
                maxfd = new_fd;

            tv.tv_sec = 1;
            tv.tv_usec = 0;
            retval = select(maxfd + 1, &rfds, NULL, NULL, &tv);
            if (retval == -1) {
                printf("select error %s", strerror(errno));
                break;
            } else if (retval == 0) {
                continue;
            } else {
                if (FD_ISSET(0, &rfds)) {
                    bzero(buf, MAXBUF + 1);
                    fgets(buf, MAXBUF, stdin);
                    if (!strncasecmp(buf, "quit", 4)) {
                        printf("#INFO: Exit Server！\n");
                        break;
                    }

                    len = send(new_fd, buf, strlen(buf) - 1, 0);
                    if (len < 0){
                        printf("#ERR: Send %s failed, error %d, %s\n",buf, errno, strerror(errno));
                        break;
                    }
                }
                if (FD_ISSET(new_fd, &rfds)) {

                    bzero(buf, MAXBUF + 1);
                    len = recv(new_fd, buf, MAXBUF, 0);
                    if (len > 0)
                        printf("client: %s(%d) \n",buf, len);
                    else {
                        if (len < 0)
                            printf("#ERR: Recv msg error %d, %s\n",errno, strerror(errno));
                        else
                            printf("#INFO: Client over connection\n");
                        break;
                    }
                }
            }
        }
        close(new_fd);
    }
    close(sockfd);
    return 0;
}

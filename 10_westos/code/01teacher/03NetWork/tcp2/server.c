/*************************************************************************
	> File Name: server.c
	> Author: 
	> Mail: 
	> Created Time: 二 11/22 10:20:10 2016
 ************************************************************************/

#include<stdio.h>
#include <string.h>//memset strlen
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>

#include <arpa/inet.h>

/*
unistd.h 中所定义的接口通常都是大量针对系统调用的封装（英语：wrapper functions）
如 fork、pipe 以及各种 I/O 原语（read、write、close 等等）
*/
#include <unistd.h>

#define MAX_STR 256
int count=0;
int main(){
    
    char buf[MAX_STR];
    char sayHello[]="Good morning Mr S!";
    int serverFd;
    serverFd=socket(AF_INET,SOCK_STREAM,0);
    
    int acceptFd;   

    struct sockaddr_in clientAddr;
    int clientLen;

    struct sockaddr_in serverAddr;
    memset(&serverAddr,0,sizeof(serverAddr));
    serverAddr.sin_family=AF_INET;
    serverAddr.sin_port= htons(12345);
    serverAddr.sin_addr.s_addr=htonl("127.0.0.1");
    
    bind(serverFd,(struct sockaddr_in *)&serverAddr,sizeof(serverAddr));
    
    printf("Socket has been created and bind\n");
    
    listen(serverFd,5);
    
    
      while(1)
    {
        printf("--------------------------%d\n",count++);
    
        printf("Now listening...\n");
        /* 接受客户端申请的连接 */
        acceptFd = accept(serverFd,(struct sockaddr*)&clientAddr,(socklen_t*)&clientLen);
        //acceptFd = accept(serverFd, NULL, NULL);

        /* 如果client成功连接到server, 则执行 */
        if(acceptFd >= 0){
            printf("Now the link has been connected.\n");

            /* 从客户端的套接字中提取出IP地址 和其他信息*/
            int clientip = clientAddr.sin_addr.s_addr;
            printf("clientLen=%d\n",clientLen);
            printf("Client ip : %d.%d.%d.%d\n",clientip&255,(clientip>>8)&255,
                    (clientip>>16)&255,(clientip>>24)&255);
            printf("Client prot : %d\n",ntohs(clientAddr.sin_port));



            /* 使用send向client发送信息 */
            sprintf(buf,"THE SEND MSG");

            printf("[SEND] Starting sending [send] msg ...\n");

            send(acceptFd, (void*)buf, strlen(buf),0);//发送数据 strlen(buff) bytes数据

            recv(acceptFd, (void*)buf, MAX_STR, 0 );//接收客户端反馈，成功或失败？//MAXN_STR：最大努力接收

            if(strlen(buf) > 0)
                printf("[SUCC] Sending succeed.\n");
            else
                printf("[FAIL] Sending failed.\n");

            /* 关闭此连接 */
            close(acceptFd);
            printf("Disconnect the link.\n");

        }else{
            /*  与client连接失败 */
            printf("ERROR: Failed while establish the link!\n");
        }
    }
    close(serverFd);
    
    return 0;
}


int a=10,b=10;
int ret = add(a,b);

int add(int x ,int y)
{
    return x+y;
}

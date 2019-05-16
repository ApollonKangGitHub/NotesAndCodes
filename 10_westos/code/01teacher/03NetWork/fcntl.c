/*************************************************************************
	> File Name: fcntl.c
	> Author: 
	> Mail: 
	> Created Time: 一 11/21 14:20:03 2016
 ************************************************************************/

#include<stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#define MSG_TRY "try again\n"

int main(void)
{
    char buf[10];
    int n;
    int flags;
    flags = fcntl(STDIN_FILENO, F_GETFL);
    flags |= O_NONBLOCK;    //set the standard input with non-block flag
    if (fcntl(STDIN_FILENO, F_SETFL, flags) == -1) {
        perror("fcntl");
        exit(1);
    }

tryagain:
    n = read(STDIN_FILENO, buf, 10);  //read input from the standard input
    if (n < 0) {
        if (errno == EAGAIN) {    //EAGAIN: try again
            sleep(3);        //wait for 3 seconds
            write(STDOUT_FILENO, MSG_TRY, strlen(MSG_TRY));
            goto tryagain;    //loop
        }
        perror("read stdin");
        exit(1);
    }
    write(STDOUT_FILENO, buf, n);   //standard input -> stabdard output
    return 0;
}

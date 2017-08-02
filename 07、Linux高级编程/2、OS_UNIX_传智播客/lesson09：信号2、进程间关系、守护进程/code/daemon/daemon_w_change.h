#ifndef _DEAMON_CHANGE_H_
#define _DEAMON_CHANGE_H_

#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<time.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

void sys_err(const char *);
void create_daemon(void);

#endif

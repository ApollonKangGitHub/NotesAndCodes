#ifndef _MULTI_PROCESS_COPY_H_
#define _MULTI_PROCESS_COPY_H_

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/mman.h>
#include<unistd.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>

/*定义单进程映射缓冲区的大小,映射大小必须是一页的倍数*/
#define MMAP_SIZE 4096 * 2

/*设定默认的进程数目*/
#define DFL_PROC_NUM 32

void deal_multi_process_copy(const char *,const char *);
void multi_process_mmap(const int, const char *, const char *);
void recovery_process_resource(void);
void fork_mmap(const int, const char *, const char *);
void mmap_file_memory(const int,const int,const int,const int,char **);

#endif

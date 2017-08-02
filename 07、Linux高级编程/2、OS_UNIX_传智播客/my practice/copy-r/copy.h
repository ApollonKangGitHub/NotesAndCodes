#ifndef _COPY_H_
#define _COPY_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define BUF_SIZE 8092
#define PATH_SIZE 1024
#define FILE_MODE 0777
#define DIR_MODE 0777

void sys_err(const char *);
void deal_dir(char *,char *);
void deal_copy(char *, char *);
void copy_file(char *, char *);
void read_write(void);
void mkdir_newdir(char *);
void get_allpath(char *, char *, char *, char *);
void init_allpath(char *, char 	*, char *, char *, char *);

#endif


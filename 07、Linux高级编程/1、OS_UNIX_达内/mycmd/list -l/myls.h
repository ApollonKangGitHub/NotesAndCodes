#ifndef _MYLS_H_
#define _MYLS_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<dirent.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/types.h>
#include<pwd.h>
#include<grp.h>
#include<time.h>

void error_print(const char *);
void mylist_dir(const char *);
void list_message(const char *,const struct stat *);
void file_type(const struct stat *);
void file_power(const struct stat *);
void file_power_char(mode_t,mode_t,const char);
void id_to_string(const struct stat *);
void timet_to_tm(const struct stat *);

#endif

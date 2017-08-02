#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUF_SIZE 1024
int main(void)
{
    /*
     *Qt中PATH中不包含当前路径
     *故用绝对路径打开
    */
    char * path = "F:\\Computer\\Notes_code\\01_C_C++\\03_C++"
                  "\\02_wang_gui_lin_C++\\mycode\\lesson3"
                  "\\string_homework\\file.txt";
    FILE *fp = fopen(path, "r+");
    if(fp == NULL){
        printf("open error");
        return -1;
    }
    //获取文件行数
    int line_cnt = 0;
    char buf[BUF_SIZE] = {0};
    while(fgets(buf, BUF_SIZE, fp) != NULL)
        line_cnt++;
    //文件指针移到文件首
    fseek(fp, 0, SEEK_SET);

    //分配line_cnt个字符串指针的空间
    char **p = (char **)malloc((line_cnt+1) * sizeof(char *));
    char **pt = p;

    while(fgets(buf, BUF_SIZE, fp) != NULL){
        int len = strlen(buf);
        *pt = (char *)malloc(len + 1);
        //将文件每一行字符串复制到新分配的空间
        strcpy(*pt, buf);
        pt++;
    }
    *pt = NULL;

    while(*p)
           printf("%s",*p++);

    fclose(fp);
    return 0;
}


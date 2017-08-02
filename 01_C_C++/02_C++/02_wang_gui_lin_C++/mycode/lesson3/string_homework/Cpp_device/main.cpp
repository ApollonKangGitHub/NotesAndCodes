#include <iostream>
#include <string.h>
#include <stdlib.h>

#define BUF_SIZE 1024
using namespace std;

int main()
{
    char * path = "F:\\Computer\\Notes_code\\01_C_C++\\03_C++"
                  "\\02_wang_gui_lin_C++\\mycode\\lesson3"
                  "\\string_homework\\file.txt";
    FILE *fp = fopen(path, "r+");
    if(fp == NULL){
        printf("open error");
        return -1;
    }
    int line_cnt = 0;
    char buf[BUF_SIZE] = {0};
    while(fgets(buf, BUF_SIZE, fp) != NULL)
        line_cnt++;
    rewind(fp);

    string * str = new string[line_cnt];
    string * pstr = str;

    while(fgets(buf, BUF_SIZE, fp) != NULL)
        *pstr++ = buf;//比C简化许多

    for(int i=0; i<line_cnt; i++)
        cout<<str[i];

    fclose(fp);
    return 0;
}


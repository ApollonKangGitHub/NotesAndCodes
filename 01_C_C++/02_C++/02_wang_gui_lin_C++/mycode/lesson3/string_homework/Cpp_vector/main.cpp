#include <iostream>
#include <vector>

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
    vector<string> vs;
    char buf[BUF_SIZE] = {0};

    while(fgets(buf, BUF_SIZE, fp) != NULL)
        vs.push_back(buf);

    for(int i=0; i<vs.size(); i++)
        cout<<vs[i];
    fclose(fp);

    return 0;
}


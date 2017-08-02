#include <iostream>
#include <stdio.h>
#include <ios>
#include <fstream>

using namespace std;

class MyFstream
{
public:
    MyFstream(const char * path, char * mode){
        fp = fopen(path, mode);
    }
    char get(){
        return fgetc(fp);
    }
    void put(char ch){
        fputc(ch, fp);
    }
    void seek(int offset, int whence){
        fseek(fp, offset, whence);
    }
private:
    FILE *fp;
};
int main()
{
#if 1
    fstream fs("kang.txt", ios::in|ios::out|ios::trunc);
    fs.put('a');
    fs.seekg(0, ios::beg);
    char ch = fs.get();
    cout<<ch<<endl;
#endif

    MyFstream ms("yuan.txt", "w+");
    ms.put('b');
    ms.seek(0,SEEK_SET);
    char ch2 = ms.get();
    cout<<ch2<<endl;
    return 0;
}


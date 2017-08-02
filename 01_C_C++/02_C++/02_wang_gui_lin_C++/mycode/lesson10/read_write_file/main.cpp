/*
 * read时的问题一般比较大(遇到空格、\n等很多问题需要处理)，
 * 而写文件时问题不多
*/
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    fstream fsr("kang.txt", ios::in|ios::out|ios::trunc);
    if(!fsr){
        cout<<"open kang.txt error!"<<endl;
    }
    fstream fsw("yuan.txt", ios::in|ios::out|ios::trunc);
    if(!fsw){
        cout<<"open yuan.txt error!"<<endl;
    }

    char buf[1024];
    fsr<<"12345 67890"<<endl;
    fsr<<"12345 67890"<<endl;
    fsr<<"12345 67890"<<endl;
    fsr<<"12345 67890"<<endl;
    fsr<<"12345 67890"<<endl;

    fsr.seekg(0,ios::beg);
    fsr>>buf;//遇到空格停止读取
    cout<<buf<<endl;
#if 0
    /*按个读*/
    char ch;
    fsr.seekg(0,ios::beg);
    while(fsr.get(ch),!fsr.eof()){//一个字符一个字符读取，但是效率不高
        fsw.put(ch);
    }
#endif

#if 0
    /*按条读(空格、换行等为一条的结束)*/
    char bufr[1024];
    fsr.seekg(0,ios::beg);
    while(fsr>>buf, !fsr.eof()){//空格被“吃了”不好用
        cout<<buf;
        fsw<<buf;
    }
#endif
#if 1
    /*按行读，换行为一行的结束*/
    char bufr[1024];
    fsr.seekg(0,ios::beg);
    while(fsr.getline(buf,1024,'\n') || !fsr.eof()){//空格被“吃了”不好用
        cout<<buf<<endl;
        fsw<<buf<<endl;//需要将getline()给ignore()的'\n'补上
        //但是在Windows中：如果最后一行没有'\n'，
        //自己加上的'\n'又改变了副本(最后一行多了个换行),
        //与原本不在内容匹配。但是Linux的vim总会自动加上'\n'，此问题不严重
        //但是非vim打开的文件就不会自动加(如open->write->close就没经过vim)
    }
#endif
    fsr.close();
    fsw.close();

    return 0;
}


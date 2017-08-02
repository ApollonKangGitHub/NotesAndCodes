#include <iostream>
#include <fstream>
#include <ios>
#include <sys/stat.h>
#include <time.h>
/*
 * 注意：
 * ofstream默认权限：ios::out|ios::trunc
 * ifstream默认权限：ios::in
 * fstream默认权限：ios::in|ios::out|ios::app
 *
 * ios::in输入  ios::out输出    ios::app末尾添加
 * ios::trunc完全覆盖  ios::binary以二进制方式打开文件
*/
using namespace std;

//所有流类对象都重载了>>和<<
int main()
{
#if 1
    /*此时的输入输出是针对当前进程而言，而不是对文件而言*/
    ofstream ofs("kangruojin.txt");
    if(!ofs){
        cout<<"open error"<<endl;
    }
    ofs<<12<<" "<<34<<" "<<56<<endl;

    ifstream ifs("kangruojin.txt");
    if(!ifs){//重载了！运算符
        cout<<"open error"<<endl;
    }
    int a,b,c;
    ifs>>a>>b>>c;
    cout<<a<<b<<c<<endl;
    ifs.close();//刷新缓冲区，链接数-1
    ofs.close();//刷新缓冲区，链接数-1
    /*设置或许有问题：生成的文件不能显示？*/
#endif
#if 1
    fstream fs("kang.txt", ios::in | ios::out | ios::app);
    fs<<102<<" "<<304<<" "<<506<<endl;//fs.operator <<(),输出到文件中

    fs.seekp(0,ios::beg);

    int x,y,z;
    fs>>x>>y>>z;//fs.operator >>(),从文件中输入，遇到空格/Tab/回车换行等结束
    cout<<x<<y<<z<<endl;//cout.operator <<(),输出到屏幕中
    fs.close();//刷新缓冲区，链接数-1
#endif
    /* 注意：当将ios::app换成ios::trunc时由于fstream打开时清空了文件，
     * 但是如果stat之前不关闭(fs.close();)文件写的内容还没被刷新进去，
     * 所以测出来的结果会是0，如果stat之前关闭了，就不存在这种问题了
     */
    struct stat mes;
    int ret = stat("kang.txt", &mes);
    if(ret < 0){
        printf("stat error");
        return -1;
    }
    cout<<"sizeof(kang.txt):"<<mes.st_size<<endl;
    cout<<"atime:"<<ctime(&mes.st_atime);
    cout<<"mtime:"<<ctime(&mes.st_mtime);
    cout<<"ctime:"<<ctime(&mes.st_ctime);
    cout<<"mode:"<<hex<<mes.st_mode<<endl;
    cout<<"LinkNumber:"<<mes.st_nlink<<endl;

    return 0;
}


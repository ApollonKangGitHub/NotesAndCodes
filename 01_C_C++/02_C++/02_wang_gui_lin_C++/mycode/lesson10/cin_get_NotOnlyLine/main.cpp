#include <iostream>
#include <string.h>
using namespace std;

int main()
{
#if 0
    int a;
    double b;
    char buf[1024];

    cin>>a>>b>>buf;
    cout<<"a: "<<a<<endl;
    cout<<"b: "<<b<<endl;
    cout<<"buf: "<<buf<<endl;//遇到空格自动结束输入
#endif
#if 0
    char ch;
    int i = 0;

    while((ch = cin.get()) != EOF){
        cout.put(ch);
    }
#endif
#if 0
/*与上面的方式等效*/
    while(cin.get(ch), !cin.eof()){
        cout.put(ch);
    }
#endif
#if 0
    char a1,b1,c1,d1;
    cin.get(a1).get(b1).get(c1).get(d1);
    cout<<a1<<b1<<c1<<d1<<endl;
#endif
#if 1
    /*输入kangruojingreat[enter]测试，发现缓冲区的上一次的直接被读取到*/
    char buf[1024];
    cin.get(buf,10,'i');//遇到i便结束
    cout<<"buf:"<<buf<<endl;

    //cin.ignore(1);//越过一个缓冲区的字符
    memset(buf, 0, 1024);
    cin.get(buf,10,'\n');//遇到\n回车便结束
    cout<<"buf:"<<buf<<endl;

    //cin.ignore(1);
    memset(buf, 0, 1024);
    cin.get(buf,10,'\n');//遇到\n回车便结束
    cout<<"buf:"<<buf<<endl;

    /*
     * 总结：
     * 去读n个字符，在读完n-1个之前，遇到截止符时，停止读并返回；
     * 截止符并没有被读到buf之中，也没有从流对象中消失或者越过；
     * 在为满足停止读取的条件之前一直处于阻塞状态，等待输入；
     * 最多能读取到n-1个，留出的空间给'\0'
    */
#endif
    return 0;
}


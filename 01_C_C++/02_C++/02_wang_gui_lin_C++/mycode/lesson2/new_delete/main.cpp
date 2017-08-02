#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

int main()
{
//1
    /*申请普通变量堆空间,new创建了一块匿名的堆中空间，并将其地址返回给指针*/
    //int *p = (int *)malloc(sizeof(int));
    //int *p = static_cast<int*>(malloc(sizeof(int)));
    int *p = new int;
    int *q = new int(200);
    p = q;

    delete p;
    delete q;
//2
    /*申请字符串对上空间*/
    cout<<"*p="<<*p<<"\t"<<"*q="<<*q<<endl;

    string * ps = new string("Canada");
    cout<<*ps<<endl;
    *ps = "China";
    cout<<*ps<<endl;

    delete ps;
//3
    /*申请自定义类型变量堆上空间*/
    struct Kan{
        int age;
        string name;
    };
    Kan * stu = new Kan{21, "kangruojin"};
    cout<<"age:"<<stu->age<<"\t"<<"name"<<stu->name<<endl;

    delete stu;
//4
    /*申请数组堆上空间*/
    char * ch = new char[40];
    strcpy(ch, "China");
    cout << ch << endl;

    int * pi = new int[5]{0};
    memset(pi, 0, sizeof(int[5]));// 等效于全部直接初始化为0
    for(int i = 0; i<5; i++)
        cout<<pi[i]<<"\t";
    cout<<endl;

    delete []ch;
    delete []pi;
//5
    /*指针数组*/
    char **ppi = new char*[5]{NULL};
    ppi[0] = new char[20]{0};
    strcpy(ppi[0], "point array[0]");
    ppi[1] = "point array[1]";
    ppi[2] = "point array[2]";
    while(*ppi)
        cout<<*ppi++<<endl;

    delete []ppi;
//6
    /*二维数组*/
    int (* parr)[4] = new int[3][4]{{0}};
    for(int i = 0; i < sizeof(int[3][4])/sizeof(int[4]); i++){
        for(int j = 0; j < 4; j++){
            cout<<parr[i][j]<<"\t";
        }
        cout<<endl;
    }

    delete []parr;
//7
    /*
    int * s = malloc(2);
    delete s;//delete存在析构，所以这样会出错
    int * n = new int;
    free(n);//free()不会出错，但也不应该使用
    */

//8
     //C++ new对申请失败的处理，不能直接采用malloc类似的if(p == NULL){printf("err");}来处理
     //C++的异常处理(尽量不要使用C++的异常)
//不推荐
    try{
        int *perr = new int[1024*1024*1024];//失败出错会抛出异常
     }catch(const std::bad_alloc err){
        cout<<"new error"<<endl;
        cout<<err.what()<<endl;//打印出错原因
        return -1;
     }//这种处理方式看起来很臃肿
     //delete []perr;
//推荐
    int *pstd = new (std::nothrow) int[10];//nothrow不抛出异常
    if(pstd == NULL){
        cout<<"new error"<<endl;
        return -1;
    }
    return 0;
}


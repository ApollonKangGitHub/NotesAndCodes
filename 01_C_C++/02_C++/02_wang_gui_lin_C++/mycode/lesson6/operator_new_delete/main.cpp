#include <iostream>
//#include <stdlib.h>
#include <string.h>

using namespace std;
/*
    void *operator new(size_t)
    void operator delete(void *)
    void *operator new[](size_t)
    void operator delete[](void *)
*/

class A{
public:
    A(){cout<<"A()"<<endl;}
    ~A(){cout<<"~A()"<<endl;}
    void func(){
        cout<<"I'am function in A"<<endl;
    }
#if 1
    void * operator new(size_t size){
        cout<<"size = "<<size<<endl;
        cout<<"operator new()"<<endl;
        void * p = malloc(size);
        memset(p, 0, size);
        ((A*)p)->data = 1;//定制化的初始化
        return p;
    }
    void operator delete(void * p){
        cout<<"operator delete()"<<endl;
        free(p);
    }
#endif
private:
    int data;
};
#if 1
void *operator new[](size_t size)
{
    cout<<"size = "<<size<<endl;
    cout<<"operator new[]()"<<endl;
    void * p = malloc(size);
    memset(p, 0, size);
    return p;
}
void operator delete[](void * p)
{
    cout<<"operator delete[]()"<<endl;
    free(p);
}
#endif
int main()
{
    /*定制化：
        指定的类用重载的new、delete、new[]、delete[]
        而其他的依然使用系统默认的new、delete、new[]、delete[]
        只需要将重载的operator声明从全局的变为具体的类的成员函数
        如果是全局的，则所有堆空间申请回收都会调用重载的
    */
    A * a = new A[5];//调用的重载new[]会自动调用构造函数
    //delete a;
    delete []a;

    A * b = new A;
    delete b;
    return 0;
}


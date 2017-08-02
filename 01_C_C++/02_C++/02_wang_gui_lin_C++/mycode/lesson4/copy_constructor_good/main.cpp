/*
 * 拷贝构造发生的时机：
 * ①为对象赋值时（定义时直接赋值/之后的赋值）
 * ②传参或返回对象时（但是传参为引用时，不会调用拷贝构造函数）
 *
 * 传参：
 * 对于普通变量而言传引用的效果不明显，对于类对象而言，传对象的效率很高
 * 因为，传引用相当于扩大了原对象的作用于，不会去调用拷贝构造函数
 *
 * 返回值：
 * 栈上的对象是可以返回的，但是栈上的对象的引用不能返回
 * 除非，返回的引用是对象本身，
 * eg：对象返回*this，其原本就属于main中的调用对象
*/
#include <iostream>

using namespace std;

class Test{
public:
    Test(){
        cout<<this<<" constructor"<<endl;
    }
    ~Test(){
        cout<<this<<" destructor"<<endl;
    }
    Test(const Test & another){
        cout<<this<<" copy constructor from "<<&another<<endl;
    }
    Test & operator=(Test & another){
        cout<<this<<" operator= "<<&another<<endl;
    }
};

Test func(Test A, Test& B){//拷贝构造,不拷贝
    return B;
    /*
     * 返回值：
     * ①若main不接收，则先在main的栈上开辟一块匿名空间，
     * 然后将B拷贝到这块匿名空间(临时的)，无权访问匿名空间，会进行拷贝构造。
     * ②如果main函数接收返回值，且是在接收之前便定义好接收的对象，
     * 则是有名空间接收，直接赋值运算符重载，不存在拷贝构造
     * ③若main函数在接收返回值时定义接收的对象，则是拷贝构造
     *
     */
}

int main()
{
    Test A;
    Test B;
    B = A;//赋值运算符重载，穿着马甲的浅拷贝（对于自定义且未重载“=”的类对象来说）
    Test C = A;//拷贝构造

    func(A, B);//一次拷贝构造


    return 0;
}


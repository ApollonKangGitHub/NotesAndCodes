/*
 * C++中有一种设计原则叫依赖倒置。也是基于多态的。
 * 定义：
 * 高层模块不应该依赖低层模块，二者都应该依赖其抽象；
 * 抽象不应该依赖细节；细节应该依赖抽象。
 * 依赖倒置原则的核心思想是面向接口编程
 *
 * 下例中：
 * Mother 类与接口 IReader 发生依赖关系，而 Book 和 Newspaper 都属于读物的范畴，
 * 他们各自都去实现 IReader 接口，这样就符合依赖倒置原则了
*/
#include <iostream>
using namespace std;

class IReader // InterfaceReader,中间抽象作为接口
{
public:
    virtual string getContents() = 0;
};

class Book:public IReader
{
public:
    string getContents(){
        return "Once upon a time there was a mountain, "
               "there was a temple in the mountains. "
               "There was a young monk in the temple";
    }
};
class NewsPaper:public IReader
{
    public:
    string getContents(){
        return "Trump, the US presidential election";
    }
};

class Mother
{
public:
    void tellStroy(IReader *i){
        cout<<i->getContents()<<endl;
    }
};
int main()
{
    Mother m;
    Book *b = new Book;
    NewsPaper *n = new NewsPaper;
    cout<<"Mother start to tell story:"<<endl;
    m.tellStroy(b);
    cout<<"Mother start to tell news:"<<endl;
    m.tellStroy(n);
    delete b;

    return 0;
}
/*
 *  依赖倒置原则基于这样一个事实：相对于细节的多变性，抽象的东西要稳定的多。以抽
 *  象为基础搭建起来的架构比以细节为基础搭建起来的架构要稳定的多。在 c++中，抽象指的是
 *  抽象类(c++中称为接口)，细节就是具体的实现类，使用接口或者抽象类的目的是制定好规范
 *  和契约，而不去涉及任何具体的操作，把展现细节的任务交给他们的实现类去完成。
*/

/*
 * 典型的数据结构之一：栈
 * 底层的存储空间，类型一致，push的数据与底层保持一致，pop的数据与顶层保持一致
 *
 * 类模板是类的抽象，类是类模板的实例。
 * 此时的类是类模板；类模板-->可以生成模板类-->可以生成类对象
*/
#include <iostream>

using namespace std;

#define STACK_SIZE 1024

template<typename T>//在类之前与类的外部定义的成员函数之前均要加，(语法规则)
class Stack{
public:
    Stack(int size = 1024){
        top = 0;
        space = new T[size];
        _size = size;
    }
    //Stack(const Stack & another);
    bool isEmpty();
    bool isFill();
    void push(T c);
    T pop();
    ~Stack(){
        delete space;
    }
private:
    T * space;
    int top;
    int _size;
};

//外部定义，Stack<T>表示该函数是模板类的函数，与Stack::func()还是不同的
template<typename T>
bool Stack<T>::isEmpty(){
    return (top == 0);
}
template<typename T>
bool Stack<T>::isFill(){
    return (top == _size);
}
template<typename T>
void Stack<T>::push(T c){
    space[top++] = c;
}
template<typename T>
T Stack<T>::pop(){
    return (space[--top]);
}

int main(void)
{
    //Stack-->Stack<int>
    Stack<char> st(26);

    for(char v='a'; !st.isFill() && v!='z'+1; v++)
        st.push(v);

    while(!st.isEmpty())
        cout<<st.pop()<<" ";
    cout<<endl;

    Stack<int> st1(26);
    for(char v='a'; !st1.isFill() && v!='z'+1; v++)
        st1.push(v);

    while(!st1.isEmpty())
        cout<<st1.pop()<<" ";
    cout<<endl;

    return 0;
}


/*
	l-value specifies const object
	l即为left，错误描述为左值为常量对象

	一般要是不需要改变值，就在函数体前面加上const，增强代码的安全性
*/
# include <iostream>
using namespace std;

class Human
{
public:
	void accept_data(int x,int y)/*const*/{i = x; j = y;}//若在函数体前面加上const，则i和j的值将为常量，无法完成赋值运算会报错
	int return_data()const{return i*j;}//该函数在函数体前加上const对i与j的值都没有改变所以不会报错
private:
	int i ;
	int j ;
};

int main(void)
{
	Human Message;
	
	Message.accept_data(2,3);
	cout << "两数相乘结果为：" << Message.return_data() << endl;
	Message.accept_data(4,7);
	cout << "两数相乘结果为：" << Message.return_data() << endl;

	return 0;
}
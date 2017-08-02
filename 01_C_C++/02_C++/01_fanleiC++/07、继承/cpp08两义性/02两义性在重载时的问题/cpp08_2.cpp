# include <iostream>
using namespace std;
class ONE
{
public:
	void hello(){cout << "基类ONE的hello函数" << endl;}
	void hello(int i)
	{
		cout << "基类ONE的带参数hello函数";
		cout << "hello(i):" << i << endl;
	}
	void print(int j)
	{
		cout << "基类ONE的带参数print函数";
		cout << "hello(j):" << j << endl;
	}
};

class TWO:public ONE
{
public:
	void hello(){cout << "子类TWO的hello函数" << endl;}
	void print(){cout << "子类TWO的print函数" << endl;}

	void print(int j)const//加const与不加const在虚函数中的区别会很明显，此处区别不明显
	{
		cout << "基类TWO的带参数print函数";
		cout << "hello(j):" << j << endl;
	}

};

int main (void)
{
	ONE Jack;
	TWO Mike;

	Jack.hello();
	Jack.hello(1245);
	Mike.hello();
	//Mike.hello(2);
	//虽然有参数区别，不会导致函数调用时的无法分辨，但是很仍然会出错，因为基类中带参数的重载函数被子类的同名的hello函数隐藏掉了。
	//子类中hello函数没有参数，编译器直接找到函数名匹配的子类中的hello函数，不会再去基类中寻找带参数的hello函数
	//但是子类中hello函数又没有参数导致出错，其出错原因还是编译器没有找到真正要用的hello函数（以为找到了），两义性则是无法区分（知道没找到）
	Mike.ONE::hello(2);//加上作用域操作符后就不会出错了

	//如果对于原有继承的基类中的函数或者数据要更新，旧的（基类）部分已经被淘汰，在不动原有基类的前提下，只需要在子类中重新定义这个函数即可
	//这样继承的一部分可以直接使用，一部分被子类更新的成员覆盖，加const为完全覆盖，不加const为仅仅隐藏
	Mike.print(2451);
	Mike.ONE::print(1457);
	
	return 0;
}
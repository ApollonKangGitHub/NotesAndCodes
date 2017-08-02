# include <iostream>
using namespace std;

class rectangle
{
public:
	rectangle(){cout << "构造函数运行中..." << endl; cout << "构造一个长方形" << endl;}
	rectangle(int l, int w)
	{
		cout << "构造函数运行中..." << endl;
		length = l; width = w;
		cout << "长方形的面积为：" << length * width << endl;
	}
	rectangle(int l, int w, int h)
	{
		cout << "构造函数运行中..." << endl;
		length = l;
		width = w;
		height = h;
		cout << "长方体的体积为：" << length * width * height << endl;
	}
	~rectangle(){cout << "析构函数运行中..." << endl;}
	int area(){return length * width;}
private:
	int length;
	int width;
	int height;
};

int main (void)
{
	rectangle a;
	rectangle b(3,4);
	rectangle c(3,4,5);

	cout << b.area() << endl;
	cout << c.area() << endl;
	return 0;
}

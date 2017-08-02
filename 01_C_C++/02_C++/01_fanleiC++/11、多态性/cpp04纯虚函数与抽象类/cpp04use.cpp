# include <iostream>
# define PI 3.14159
using namespace std;

class Shape//Shape类作为抽象类唯一一个纯虚函数只为子类提供一个接口
{
public:
	virtual double area()=0;//纯虚函数
};

class Trigon:public Shape
{
protected:
	double h,w;
public:
	Trigon(double H,double W)
	{
		h=H;
		w=W;
	}
	double area()
	{
		return h*w/2;
	}
};

class Square:public Trigon
{
public:
	Square(double H,double W):Trigon(H,W){}
	double area()
	{
		return h*w;
	}
};
class Circle:public Shape
{
protected:
	double radius;
public:
	Circle(double r){radius = r;}
	double area()
	{
		return radius*radius*PI;
	}
};
int main (void)
{
	Shape *p;//抽象类指针
	int choice =0;
	while(1)
	{
		bool quit=false;
		cout<<"(0)退出  (1)三角形  (2)正方形  (3)圆"<<endl;
		cout<<"请选择：";
		cin>>choice;
		switch(choice)
		{
		case 0:quit = true;
			break;
		case 1:p=new Trigon(5.0,6.0);
			cout<<"三角形面积为："<<p->area()<<endl;
			break;
		case 2:p=new Square(70.0,70.0);
			cout<<"正方形面积为："<<p->area()<<endl;
			break;
		case 3:p=new Circle(9.0);
			cout<<"圆的面积为："<<p->area()<<endl;
			break;
		default:cout<<"请输入0到3之间的数字：";
			break;
		}
		if(choice<4 && choice>0)
			delete p;
		if(quit == true)
			break;
	}
	return 0;
}
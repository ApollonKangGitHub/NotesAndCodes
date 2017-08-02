# include <iostream>
# define PI 3.14159
using namespace std;

class Shape//Shape����Ϊ������Ψһһ�����麯��ֻΪ�����ṩһ���ӿ�
{
public:
	virtual double area()=0;//���麯��
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
	Shape *p;//������ָ��
	int choice =0;
	while(1)
	{
		bool quit=false;
		cout<<"(0)�˳�  (1)������  (2)������  (3)Բ"<<endl;
		cout<<"��ѡ��";
		cin>>choice;
		switch(choice)
		{
		case 0:quit = true;
			break;
		case 1:p=new Trigon(5.0,6.0);
			cout<<"���������Ϊ��"<<p->area()<<endl;
			break;
		case 2:p=new Square(70.0,70.0);
			cout<<"���������Ϊ��"<<p->area()<<endl;
			break;
		case 3:p=new Circle(9.0);
			cout<<"Բ�����Ϊ��"<<p->area()<<endl;
			break;
		default:cout<<"������0��3֮������֣�";
			break;
		}
		if(choice<4 && choice>0)
			delete p;
		if(quit == true)
			break;
	}
	return 0;
}
# include <iostream>
using namespace std;
class A
{
public:
	virtual int get(){return 1;}
	//int get(){return 1;}
};
class B:public A
{
public:
	int get (){return 2;}
};
int main (void)
{
	while(1)
	{
		cout << "(1)����(2)����(3)�˳���";
		int choice;
		bool quit = false;
		A * p;//ֻ�е�ָ���virtualͬʱ�������ʵ�ֶ�̬����
		A p1;//ֻ����virtual������ͨ��������޷�ʵ�ֶ�̬����
		cin >> choice;
		
		switch(choice)
		{
		case 1:p = new A;
			p1 = A();
			break;
		case 2:p = new B;
			p1 = B();
			break;
		case 3:quit = true;
			break;
		default:cout<<"������1��2����3��";
			break;
		}
		if(quit == true)
		{
			break;
		}
		cout << p->get() << "\t" << p1.get() << endl;
	}
	return 0;
}
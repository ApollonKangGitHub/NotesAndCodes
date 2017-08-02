/*
	һ�����������ж�����麯��������������û����ȫ���ǻ����еĴ��麯����
	���������ҲΪ�����࣬���Ҳ��ܴ�����Ӧ�Ķ���
*/

# include <iostream>
using namespace std;

class Animal
{
public:
	Animal(int age):itsage(age){cout<<"��������...\n";}
	virtual ~Animal(){cout << "��������...\n";}
	virtual int GetAge(){return itsage;}
	virtual void Sleep()=0;
	virtual void Propagate()=0;
	virtual void Move()=0;
	virtual void Body()=0;
	virtual void Eat()=0;
	virtual void Show()=0;
private:
	int itsage;
};

class Mammalia:public Animal
{
public:
	Mammalia(int age):Animal(age){cout<<"����������...\n";}
	virtual ~Mammalia(){cout<<"����������..."<<endl;}
	virtual void Propagate(){cout<<"��������̥�����ͨ����̥����ֳ���..."<<endl;}
};

class Bird:public Animal
{
public:
	Bird(int age):Animal(age){cout<<"��������..."<<endl;}
	virtual ~Bird(){cout<<"��������..."<<endl;}
	virtual void Sleep(){cout<<"����ϲ��վ��˯��..."<<endl;}
	virtual void Eat(){cout<<"������������أ��������ǳ���..."<<endl;}
	virtual void Propagate(){cout<<"�������������ͨ����������ֳ���..."<<endl;}
	virtual void Move(){cout<<"������Է�..."<<endl;}
	virtual void Body(){cout<<"�����������ë��ǰ֫��Ϊ��..."<<endl;}
	virtual void Show(){cout<<"�����һ������Ϊ��"<<this->GetAge()<<"��"<<endl;}
};
class Human:public Mammalia
{
public:
	Human (int age):Mammalia(age){cout<<"��������..."<<endl;}
	virtual ~Human(){cout<<"��������..."<<endl;}
	virtual void Sleep(){cout<<"�����ڴ���˯��..."<<endl;}
	virtual void Eat(){cout<<"���಻̫����ʳ..."<<endl;}
	virtual void Propagate(){cout<<"����ͨ����̥��ֳ���..."<<endl;}
	virtual void Move(){cout<<"���࿿��������·..."<<endl;}
	virtual void Body(){cout<<"�������⻬������ë..."<<endl;}
	virtual void Show(){cout<<"�����һ������Ϊ��"<<this->GetAge()<<"��"<<endl;}

};
class Pig:public Mammalia
{
public:
	Pig(int age):Mammalia(age){cout<<"��������..."<<endl;}
	virtual ~Pig(){cout<<"��������..."<<endl;}
	virtual void Sleep(){cout<<"����ϲ��ſ����˯��..."<<endl;}
	virtual void Eat(){cout<<"��������ʳ�ද��..."<<endl;}
	virtual void Propagate(){cout<<"����ͨ����̥��ֳ���..."<<endl;}
	virtual void Move(){cout<<"���࿿��������·..."<<endl;}
	virtual void Body(){cout<<"�������ֲڣ�������ë..."<<endl;}
	virtual void Show(){cout<<"����ΪҪ���������˳ԣ����������һ������Ϊ��"<<this->GetAge()<<"��"<<endl;}

};
int main (void)
{
	Animal*p = 0;
	int choice = 0;
	bool quit = false;
	while(choice<4)
	{
		cout<<"(0)�˳�  (1)����  (2)����  (3)����"<<endl;
		cin>>choice;
		switch(choice)
		{
		case 0:quit = true;
			cout<<"�˳��ɹ���"<<endl;
			break;
		case 1:p = new Pig(1);
			break;
		case 2:p = new Human(75);
			break;
		case 3:p = new Bird(10);
			break;
		default:quit = true;
			cout<<"�˳��ɹ���"<<endl;
			break;
		}
		if(quit)	break;
		p->Body();
		p->Eat();
		p->GetAge();
		p->Move();
		p->Propagate();
		p->Show();
		p->Sleep();
		cout<<endl;
		delete p;
	}
	return 0;
}
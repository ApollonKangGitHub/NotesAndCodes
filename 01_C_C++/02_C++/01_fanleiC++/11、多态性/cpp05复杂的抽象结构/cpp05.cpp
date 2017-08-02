/*
	一个抽象类中有多个纯虚函数，如该类的派生没有完全覆盖基类中的纯虚函数，
	则该派生类也为抽象类，并且不能创建相应的对象。
*/

# include <iostream>
using namespace std;

class Animal
{
public:
	Animal(int age):itsage(age){cout<<"创建动物...\n";}
	virtual ~Animal(){cout << "析构动物...\n";}
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
	Mammalia(int age):Animal(age){cout<<"创建哺乳类...\n";}
	virtual ~Mammalia(){cout<<"析构哺乳类..."<<endl;}
	virtual void Propagate(){cout<<"哺乳类是胎生动物，通过胚胎来繁殖后代..."<<endl;}
};

class Bird:public Animal
{
public:
	Bird(int age):Animal(age){cout<<"创建鸟类..."<<endl;}
	virtual ~Bird(){cout<<"析构鸟类..."<<endl;}
	virtual void Sleep(){cout<<"鸟类喜欢站着睡觉..."<<endl;}
	virtual void Eat(){cout<<"极个别鸟类吃素，其它都是吃肉..."<<endl;}
	virtual void Propagate(){cout<<"鸟类是卵生动物，通过排卵来繁殖后代..."<<endl;}
	virtual void Move(){cout<<"鸟类可以飞..."<<endl;}
	virtual void Body(){cout<<"鸟类体表被覆羽毛，前肢变为翼..."<<endl;}
	virtual void Show(){cout<<"鸟类的一般寿命为："<<this->GetAge()<<"年"<<endl;}
};
class Human:public Mammalia
{
public:
	Human (int age):Mammalia(age){cout<<"创建人类..."<<endl;}
	virtual ~Human(){cout<<"析构人类..."<<endl;}
	virtual void Sleep(){cout<<"人类在床上睡觉..."<<endl;}
	virtual void Eat(){cout<<"人类不太吃生食..."<<endl;}
	virtual void Propagate(){cout<<"人类通过胚胎繁殖后代..."<<endl;}
	virtual void Move(){cout<<"人类靠两条腿走路..."<<endl;}
	virtual void Body(){cout<<"人类体表光滑，无羽毛..."<<endl;}
	virtual void Show(){cout<<"人类的一般寿命为："<<this->GetAge()<<"年"<<endl;}

};
class Pig:public Mammalia
{
public:
	Pig(int age):Mammalia(age){cout<<"创建猪类..."<<endl;}
	virtual ~Pig(){cout<<"析构猪类..."<<endl;}
	virtual void Sleep(){cout<<"人类喜欢趴着着睡觉..."<<endl;}
	virtual void Eat(){cout<<"猪类是杂食类动物..."<<endl;}
	virtual void Propagate(){cout<<"猪类通过胚胎繁殖后代..."<<endl;}
	virtual void Move(){cout<<"猪类靠四条腿走路..."<<endl;}
	virtual void Body(){cout<<"猪类体表粗糙，被覆猪毛..."<<endl;}
	virtual void Show(){cout<<"猪因为要被人类宰了吃，所以猪类的一般寿命为："<<this->GetAge()<<"年"<<endl;}

};
int main (void)
{
	Animal*p = 0;
	int choice = 0;
	bool quit = false;
	while(choice<4)
	{
		cout<<"(0)退出  (1)猪类  (2)人类  (3)鸟类"<<endl;
		cin>>choice;
		switch(choice)
		{
		case 0:quit = true;
			cout<<"退出成功！"<<endl;
			break;
		case 1:p = new Pig(1);
			break;
		case 2:p = new Human(75);
			break;
		case 3:p = new Bird(10);
			break;
		default:quit = true;
			cout<<"退出成功！"<<endl;
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
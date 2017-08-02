#include<iostream>
using namespace std;
class father
{
public:
	void smart()
	{
		cout << "父亲很聪明\n";
	}
	//virtual void beautiful(){}//该函数在父类中没有任何作用，子类本应从母类中继承，但是没有母类，父类为了给子类提供一个接口，就加上了没有任何实际功能的虚函数
	virtual ~father(){cout << "析构father"<<endl;}
};

class son:public father
{
public:
	virtual void beautiful()
	{
		cout << "儿子也很帅\n";
	}
	son(){cout << "析构son"<<endl;}
};

int main (void)
{
	father * pf;
	int choice = 0;
	while(choice<99)
	{
		bool quit=false;
		cout<<"(0)退出\t(1)父亲\t(2)儿子:"<<endl;
		cin>>choice;
		switch(choice)
		{
		case 0:quit=true;
			break;
		case 1:pf=new father;
		//	pf->beautiful();
			pf->smart();
			break;
		case 2:pf=new son;
			dynamic_cast<son*>(pf)->beautiful();//dynamic_cast将pf强制转化为son*指针。但是必须在“工程--设置--C/C++--C++语言”中勾选RTTI才可以
			//pf->beautiful();//pf为父类指针，由于父类的beautiful已经注释，所以不能通过pf调用父类中没有的成员
			pf->smart();
			delete pf;
		default:cout<<"请输入从0到2之间的数字:";
		}
		if(quit)
		{
			break;
		}
	}
	cout<<"程序结束！"<<endl;
	return 0;
}
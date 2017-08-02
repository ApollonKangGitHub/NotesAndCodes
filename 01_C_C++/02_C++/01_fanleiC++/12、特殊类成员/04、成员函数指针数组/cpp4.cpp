/*
	调用成员函数指针，必须通过类的对象来调用
	成员函数指针过于复杂，能不用尽量不用
*/
# include <iostream>
using namespace std;
class Paper
{
public:
	void read(){cout<<"纸上面的字可以读"<<endl;}
	void write(){cout<<"纸可以用来写字"<<endl;}
	void burn(){cout<<"纸可以用来生火"<<endl;}
};

typedef void (Paper::*p)();
int main (void)
{
	p func[3]={&Paper::read,&Paper::write,&Paper::burn};
	Paper *pp = 0;
	char choice[1];
	bool quit=false;
	while(!quit)
	{
		cout<<"(0)exit (1)read (2)write (3)burn"<<endl;
		cin>>choice[0];
		if(choice[0]>'3' || choice[0]<'0')
			cout<<"Please input number between zero to three:"<<endl;
		else if(choice[0]=='0')	quit=true;
		else
		{
			int n;
			pp =new Paper;//创建类的对象
			n=atoi(choice);//将字符转换为数字做下标
			(pp->*func[n-1])();
			delete pp;
		}
	}
	return 0;
}

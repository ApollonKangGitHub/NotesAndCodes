#include<iostream>
using namespace	std;
void (*p[5])(int &,int &);//全局函数指针
void square(float &x,float &y){x=x*x;y=y*y;}
void cube(float &x,float &y){x = x*x*x;y = y*y*y;}
void print(float &x,float &y){cout<<"长：	"<<x<<"宽：	"<<y<<endl;}
void Swap(float &x,float &y){float temp = x;x = y;y = temp;}
int main (void)
{
	float a=2,b=3;
	int choice = 0;
	int i;
	void(*p[5])(float &x,float &y);//局部的函数指针将全局的函数指针屏蔽掉
	for(i=0;i<5;++i)
	{
		cout<<"(0)exit  (1)平方  (2)立方  (3)交换x和y的值\n";
		cin>>choice;
		bool quit = false;
		switch(choice)
		{
		case 0:quit = true;
			break;
		case 1:p[i]=square;
			break;
		case 2:p[i]=cube;
			break;
		case 3:p[i]=Swap;
			break;
		default:p[i]=0;
			break;
		}
		if(true==quit)break;
		if(0==p[i])
		{
			cout<< "请输入一个从0到3的数字"<<endl;
			--i;//保证循环条件依旧成立
			continue;
		}
		cout<<"第"<<i+1<<"次执行，到第5次结束"<<endl;
		cout<<"初始值"<<endl;
		print(a,b);
		cout<<"现在调用函数指针数组p["<<i<<"]所指向的函数..."<<endl;
		p[i](a,b);
		cout<<"运算后："<<endl;
		print(a,b);
	}
	return 0;
}

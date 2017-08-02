/*
	取消typedef的注销
	并且将其他已注销的和已注销下一行互换注销，便可得到相同的结果
*/
#include<iostream>
using namespace	std;

//typedef void(*p)(float &,float &);//将void(*)(float &,float &)简化为p
void square(float &x,float &y){x=x*x;y=y*y;}
void cube(float &x,float &y){x = x*x*x;y = y*y*y;}
//void print(p vp, float &x, float &y)
void print(void(*p)(float &, float &), float &x, float &y)//第一个参数为函数指针，可以做参数的是函数名，如square
{
	cout<<"执行函数前："<<endl;
	cout<<"x:"<<x<<'\t'<<"y:"<<y<<endl;
	//vp(x,y);
	p(x,y);
	cout<<"执行函数后："<<endl;
	cout<<"x:"<<x<<'\t'<<"y:"<<y<<endl;
}
void Swap(float &x,float &y){float temp = x;x = y;y = temp;}
int main (void)
{
	float a=2,b=3;
	int choice = 0;
	int i;
	//p vp;
	void(*p[5])(float &x,float &y);
	for(i=0;i<5;++i)
	{
		cout<<"(0)exit  (1)平方  (2)立方  (3)交换x和y的值\n";
		cin>>choice;
		bool quit = false;
		switch(choice)
		{
		case 0:quit = true;
			break;
		case 1://vp=square;
			p[i]=square;
			break;
		case 2://vp=cube;
			p[i]=cube;
			break;
		case 3://vp=Swap;
			p[i]=Swap;
			break;
		default://vp=0;
			p[i]=0;
			break;
		}
		if(true==quit)break;
		//if(0==vp)
		if(p[i]==0)
		{
			cout<< "请输入一个从0到3的数字"<<endl;
			--i;
			continue;
		}
		//print(vp,a,b);//第一个参数是square、cube或者Swap,代码更加简练与规范
		print(p[i],a,b);
	}
	return 0;
}

/*
	ȡ��typedef��ע��
	���ҽ�������ע���ĺ���ע����һ�л���ע������ɵõ���ͬ�Ľ��
*/
#include<iostream>
using namespace	std;

//typedef void(*p)(float &,float &);//��void(*)(float &,float &)��Ϊp
void square(float &x,float &y){x=x*x;y=y*y;}
void cube(float &x,float &y){x = x*x*x;y = y*y*y;}
//void print(p vp, float &x, float &y)
void print(void(*p)(float &, float &), float &x, float &y)//��һ������Ϊ����ָ�룬�������������Ǻ���������square
{
	cout<<"ִ�к���ǰ��"<<endl;
	cout<<"x:"<<x<<'\t'<<"y:"<<y<<endl;
	//vp(x,y);
	p(x,y);
	cout<<"ִ�к�����"<<endl;
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
		cout<<"(0)exit  (1)ƽ��  (2)����  (3)����x��y��ֵ\n";
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
			cout<< "������һ����0��3������"<<endl;
			--i;
			continue;
		}
		//print(vp,a,b);//��һ��������square��cube����Swap,������Ӽ�����淶
		print(p[i],a,b);
	}
	return 0;
}

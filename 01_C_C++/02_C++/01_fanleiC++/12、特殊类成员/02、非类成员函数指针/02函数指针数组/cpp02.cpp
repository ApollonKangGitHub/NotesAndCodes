#include<iostream>
using namespace	std;
void (*p[5])(int &,int &);//ȫ�ֺ���ָ��
void square(float &x,float &y){x=x*x;y=y*y;}
void cube(float &x,float &y){x = x*x*x;y = y*y*y;}
void print(float &x,float &y){cout<<"����	"<<x<<"��	"<<y<<endl;}
void Swap(float &x,float &y){float temp = x;x = y;y = temp;}
int main (void)
{
	float a=2,b=3;
	int choice = 0;
	int i;
	void(*p[5])(float &x,float &y);//�ֲ��ĺ���ָ�뽫ȫ�ֵĺ���ָ�����ε�
	for(i=0;i<5;++i)
	{
		cout<<"(0)exit  (1)ƽ��  (2)����  (3)����x��y��ֵ\n";
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
			cout<< "������һ����0��3������"<<endl;
			--i;//��֤ѭ���������ɳ���
			continue;
		}
		cout<<"��"<<i+1<<"��ִ�У�����5�ν���"<<endl;
		cout<<"��ʼֵ"<<endl;
		print(a,b);
		cout<<"���ڵ��ú���ָ������p["<<i<<"]��ָ��ĺ���..."<<endl;
		p[i](a,b);
		cout<<"�����"<<endl;
		print(a,b);
	}
	return 0;
}

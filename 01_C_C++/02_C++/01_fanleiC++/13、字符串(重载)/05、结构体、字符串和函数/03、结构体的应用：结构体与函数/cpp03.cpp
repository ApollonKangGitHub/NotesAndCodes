# include<iostream>
# include<string>
using namespace std;

struct time
{
	int hour;
	int minute;
};

const int perhour = 60;
time sum(time t1,time t2);//��ֵ����
time * sum_p(time t1,time t2);//����ַ����,����Ҫ���ø��ƹ��캯��
void show(time t)
{
	cout<<t.hour<<"Сʱ"<<t.minute<<"����"<<endl;
}
int main (void)
{
	cout<<"/*��ֵ���صļ�����*//"<<endl;
	time day1 = {8,15};
	time day2 = {6,55};
	time day = sum(day1,day2);
	cout<<"����ʱ���ܼ��ϰ�ʱ�䣺"<<endl;
	show(day);
	time day3 = {9,35};
	cout<<"����ʱ���ܼ��ϰ�ʱ�䣺"<<endl;
	show(sum(day,day3));
	cout<<endl<<endl;

	cout<<"/*����ַ���صļ�����*/"<<endl;
	time *DAY = sum_p(day1,day2);
	cout<<"����ʱ���ܼ��ϰ�ʱ�䣺"<<endl;
	show(*DAY);
	time * p = sum_p(*DAY,day3);
	cout<<"����ʱ���ܼ��ϰ�ʱ�䣺"<<endl;
	show(*p);
	delete DAY;
	delete p;

	return 0;
}
time sum(time t1,time t2)
{
	time total;
	total.minute = (t1.minute+t2.minute)%perhour;
	total.hour = t1.hour+t2.hour+(t1.minute+t2.minute)/perhour;
	return total;
}

time * sum_p(time t1,time t2)
{
	time * total = new time;
	total->minute = (t1.minute+t2.minute)%perhour;
	total->hour = t1.hour+t2.hour+(t1.minute+t2.minute)/perhour;
	return total;
}
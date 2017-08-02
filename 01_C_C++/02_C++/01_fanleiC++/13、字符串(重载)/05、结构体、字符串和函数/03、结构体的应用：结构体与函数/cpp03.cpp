# include<iostream>
# include<string>
using namespace std;

struct time
{
	int hour;
	int minute;
};

const int perhour = 60;
time sum(time t1,time t2);//按值返回
time * sum_p(time t1,time t2);//按地址返回,不需要调用复制构造函数
void show(time t)
{
	cout<<t.hour<<"小时"<<t.minute<<"分钟"<<endl;
}
int main (void)
{
	cout<<"/*按值返回的计算结果*//"<<endl;
	time day1 = {8,15};
	time day2 = {6,55};
	time day = sum(day1,day2);
	cout<<"两天时间总计上班时间："<<endl;
	show(day);
	time day3 = {9,35};
	cout<<"三天时间总计上班时间："<<endl;
	show(sum(day,day3));
	cout<<endl<<endl;

	cout<<"/*按地址返回的计算结果*/"<<endl;
	time *DAY = sum_p(day1,day2);
	cout<<"两天时间总计上班时间："<<endl;
	show(*DAY);
	time * p = sum_p(*DAY,day3);
	cout<<"三天时间总计上班时间："<<endl;
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
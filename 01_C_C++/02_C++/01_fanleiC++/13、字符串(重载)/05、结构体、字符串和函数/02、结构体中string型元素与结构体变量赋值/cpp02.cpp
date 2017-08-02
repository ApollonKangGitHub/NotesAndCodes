# include<iostream>
# include<string>
using namespace std;

struct people
{
	people(int t_age,double t_weight,double t_high,string t_name,string t_native,string t_sex);
	int age;
	double weight;
	double high;
	string name;
	string native;
	string sex;
	//注意：在VC7.0之前的版本不支持在结构体中添加string型变量
	//要想使用string型字符串，就必须借用构造函数
};
people::people(int t_age,double t_weight,double t_high,string t_name,string t_native,string t_sex)
{
		age = t_age;
		weight = t_weight;
		high = t_high;
		name = t_name;
		native = t_native;
		sex = t_sex;
}
int main (void)
{
	people Jack(20,71.5,175.5,"Jack","济南","男");
	people Mike(21,65.5,173.5,"Mike","西安","男");
	cout<<Jack.name<<"的信息为："<<endl;
	cout<<"姓名："<<Jack.name<<endl;
	cout<<"年龄："<<Jack.age<<endl;
	cout<<"体重："<<Jack.weight<<endl;
	cout<<"身高："<<Jack.high<<endl;
	cout<<"出生地："<<Jack.native<<endl;
	cout<<"性别："<<Jack.sex<<endl;

	//结构体变量的赋值
	Jack = Mike;
	cout<<Jack.name<<"的信息为："<<endl;
	cout<<"姓名："<<Jack.name<<endl;
	cout<<"年龄："<<Jack.age<<endl;
	cout<<"体重："<<Jack.weight<<endl;
	cout<<"身高："<<Jack.high<<endl;
	cout<<"出生地："<<Jack.native<<endl;
	cout<<"性别："<<Jack.sex<<endl;
	return 0;
}
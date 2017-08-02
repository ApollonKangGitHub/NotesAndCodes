# include<iostream>
using namespace std;

struct people
{
	int age;
	double weight;
	double high;
	char * name;
	char * native;
	char * sex;
};
int main (void)
{
	people Jack={
		20,
		70,
		175,
		"Jack",
		"济南",
		"男"
	};

	cout<<Jack.name<<"的信息为："<<endl;
	cout<<"年龄："<<Jack.age<<endl;
	cout<<"体重："<<Jack.weight<<endl;
	cout<<"身高："<<Jack.high<<endl;
	cout<<"出生地："<<Jack.native<<endl;
	cout<<"性别："<<Jack.sex<<endl;

	return 0;
}
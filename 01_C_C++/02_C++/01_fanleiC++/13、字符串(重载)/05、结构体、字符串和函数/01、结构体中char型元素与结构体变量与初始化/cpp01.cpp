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
		"����",
		"��"
	};

	cout<<Jack.name<<"����ϢΪ��"<<endl;
	cout<<"���䣺"<<Jack.age<<endl;
	cout<<"���أ�"<<Jack.weight<<endl;
	cout<<"��ߣ�"<<Jack.high<<endl;
	cout<<"�����أ�"<<Jack.native<<endl;
	cout<<"�Ա�"<<Jack.sex<<endl;

	return 0;
}
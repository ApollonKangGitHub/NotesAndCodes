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
	//ע�⣺��VC7.0֮ǰ�İ汾��֧���ڽṹ�������string�ͱ���
	//Ҫ��ʹ��string���ַ������ͱ�����ù��캯��
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
	people Jack(20,71.5,175.5,"Jack","����","��");
	people Mike(21,65.5,173.5,"Mike","����","��");
	cout<<Jack.name<<"����ϢΪ��"<<endl;
	cout<<"������"<<Jack.name<<endl;
	cout<<"���䣺"<<Jack.age<<endl;
	cout<<"���أ�"<<Jack.weight<<endl;
	cout<<"��ߣ�"<<Jack.high<<endl;
	cout<<"�����أ�"<<Jack.native<<endl;
	cout<<"�Ա�"<<Jack.sex<<endl;

	//�ṹ������ĸ�ֵ
	Jack = Mike;
	cout<<Jack.name<<"����ϢΪ��"<<endl;
	cout<<"������"<<Jack.name<<endl;
	cout<<"���䣺"<<Jack.age<<endl;
	cout<<"���أ�"<<Jack.weight<<endl;
	cout<<"��ߣ�"<<Jack.high<<endl;
	cout<<"�����أ�"<<Jack.native<<endl;
	cout<<"�Ա�"<<Jack.sex<<endl;
	return 0;
}
/*
	2016��8��22��15:39:21
	���ֲ������ݷ�������һ�з�����Ψһ�����ǣ�
	���������๹�캯�������б����ֱ�ӶԻ��๹�캯����ʼ����ɾ�����๹�캯���жԻ����ʼ���Ĵ���
	��˱㲻����û���Ĳ��������Ĺ��캯�������ǵ��ô������Ļ��๹�캯��ֱ�ӳ�ʼ�������Ա
*/
# include <iostream>
# include <string>
using namespace std;

class father
{
protected:
	string name;
	int tall;
public:
	father(string a,int i);
	father(){cout << "�������,���캯��ִ����..." << endl;}
	void print_father(){cout << name << "���Ϊ��" << tall << endl;}
	~father(){cout << "�ͷŻ������,��������ִ����..." << endl;}
};

father::father(string a,int i)
{
	cout << "������๹�캯��" << endl;
	name = a;
	tall = i;
	print_father();
	cout << "�뿪���๹�캯��" << endl;
}

class son:public father
{
private:
	int weight;
public:
	son(string a,int i,int j);
	void print_son();
	~son(){cout << "�ͷ��������,��������ִ����..." << endl;}
};

son::son(string a,int i,int j):father(a,i)//ֱ�Ӵ��θ����๹�캯��
{
	cout<<"��������Ĺ��캯��"<<endl;
	//name = a;
	//tall = i;
	weight = j;
	cout << "�뿪���๹�캯��" << endl;
}
void son::print_son()
{
	father::print_father();
	cout << "����:" << weight << endl;
}
int main (void)
{
	son Mike("Mike",175,65);
	Mike.print_son();
	cout << "�������" << endl;
	return 0;
}
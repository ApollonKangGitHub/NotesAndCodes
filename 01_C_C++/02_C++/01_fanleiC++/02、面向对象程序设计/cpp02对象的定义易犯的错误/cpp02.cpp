/*
2016��8��4��12:31:27
*/
# include <iostream>
using namespace std;

class Human
{
public:
	int weight;
	void set_age(int x){age = x;}
	int return_age(){return age;}
private:
	int age;
};
int main (void)
{
	//Human.weight = 60;//error
	Human Tom;
	Tom.weight = 60;
	cout<<"Tom������Ϊ��"<<Tom.weight<<endl;

	//Tom.age = 18;//error
	//cout<<"Tom������Ϊ��"<<Tom.age<<endl;//error
	Tom.set_age(18);
	cout<<"Tom������Ϊ��"<<Tom.return_age()<<endl;

	return 0;
}

/*
1��Ҫʹ�ùؼ���class�����ࣻ
2��Ҫʹ���������������
3����Ҫ������������������������˵��������ʲô������������Ϊ���������һ���ڴ棻
4��������ĳ�Ա��public���г�Ա��Ҫʹ��.�������
5��ʹ�ö�����.��Ա�����ʳ�Ա���������ݳ�Ա��public���г�Ա����ֵ��
6����Ҫ������Ͷ��󣬲�Ҫ���ำֵ��
*/
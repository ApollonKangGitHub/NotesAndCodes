/*
	2016��8��4��12:41:13
	>>˽�����ݳ�Ա��Ȼ��ֵʹ���鷳�����ǰ�ȫ�Ըߣ�һ�����ݳ�Ա����Ϊ˽�г�Ա
	>>�������û����ǰ˵����Ա�ǹ��л���˽�У�Ĭ��Ϊ˽��
*/
# include <iostream>
using namespace std;

class Human
{
public:
	void set_weight(int);
	int return_weight();
private:
	int weight;
};

void Human::set_weight(int x)
{
	if(x>40 && x<120)
	{
		weight = x;
	}
	else
	{
		cout<<"����������ط�Χ��40kg����120kg֮�䣬����Ĭ��Ϊ0��\n";
		weight = 0;
	}
}
int Human::return_weight()
{
	return weight;
}
int main (void)
{
	Human Tom;
	Human LiMing;

	Tom.set_weight(110);
	cout<<"��ķ������Ϊ��kg����"<<Tom.return_weight()<<endl;
	LiMing.set_weight(310);
	cout<<"����������Ϊ��kg����"<<LiMing.return_weight()<<endl;

	return 0;
}
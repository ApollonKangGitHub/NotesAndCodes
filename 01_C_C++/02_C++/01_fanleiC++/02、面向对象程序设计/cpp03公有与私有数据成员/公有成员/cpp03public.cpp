/*
	2016��8��4��12:39:49
	�������ݳ�Ա��ֱ�ӵ��÷��ʲ���ֵ
*/
# include <iostream>
using namespace std;

class Human
{
public:
	int weight;
};
int main (void)
{
	Human Tom;
	Human LiMing;

	Tom.weight = 110;
	cout<<"��ķ������Ϊ��kg����"<<Tom.weight<<endl;
	LiMing.weight = 120;
	cout<<"����������Ϊ��kg����"<<LiMing.weight<<endl;

	return 0;
}
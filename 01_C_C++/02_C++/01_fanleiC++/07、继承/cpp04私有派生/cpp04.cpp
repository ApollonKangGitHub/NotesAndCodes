/*
	2016��8��22��12:12:18
	˽�������빫����������ͬ�㣺
	
	ͬ��
		�����ǹ�����������˽�������������Է��ʸ����˽�г�Ա��������ı�����Ա�빫�г�Ա�����Է���
	�죺
		��������ֻ�з��ʸ��ౣ����Աʱ����Ҫ��������ӹ��нӿ�
		˽���������ʸ��ౣ����Ա�빫�г�Ա��������������ӹ��нӿ�
*/
# include <iostream>
using namespace std;

class FATHER
{
protected:
	void money(){cout << "���׵�Ǯ���ҿ���ʹ��!" << endl;}
public:
	void room(){cout << "���״����ҿ���ʹ��!" << endl;}
};
class SON:private FATHER//˽�������������õ�
{
public:
	void mother_room(){room();}
	void nother_money(){money();}
};
int main (void)
{
	SON Huni;
	//Huni.room();//������ֱ�ӷ���
	Huni.mother_room();//Huni��˽��������˽���ӣ���Ҫ����ʸ��׵ĳ�Ա����ͨ���Լ��Ĺ��нӿڣ��Լ��ġ�ĸ�ס���
	//Huni.money();
	Huni.nother_money();
	
	return 0;
}
/*
	2016��8��22��17:09:07
	һ�������ɶ������������������������������һ����ͬ�Ļ�����������
	��ô������������ͬ�Ļ���ĳ�Աʱ�ͻ����������
*/
# include <iostream>
using namespace std;
class ONE
{
public:
	int num (){return 1;}
};

class TWO:public ONE
{
public:
	int num (){return 2;}
};
class THREE:public ONE
{
public:
	int num (){return 3;}
};

class FOUR:public TWO,public THREE
{
public:
	int num (){return 4;}
	int M(){return THREE::num();}
};

int main (void)
{
	FOUR NUMBER;

	cout << NUMBER.THREE::num() << endl;
	cout << NUMBER.THREE::num() << endl;
	cout << NUMBER.THREE::num() << endl;
	cout << NUMBER.THREE::num() << endl;//���ǿ���ֱ�ӵ���THREE��num����

	cout << NUMBER.M() << endl;
	cout << NUMBER.M() << endl;
	cout << NUMBER.M() << endl;
	cout << NUMBER.M() << endl;//Ҳ����ͨ��FOUR��public�ӿں�������ӵ���THREE��num�������ڶ�ε���ʱ�����ּ�ӵ��õķ������Եø�Ϊ������������������ˣ�
	return 0;
}
/*
	2016��8��22��17:09:07
	һ�������ɶ������������������������������һ����ͬ�Ļ�����������
	��ô������������ͬ�Ļ���ĳ�Աʱ�ͻ����������
*/
# include <iostream>
using namespace std;
class Human
{
public:
	void stand(){cout << "�����ܹ�ֱ������" << endl;}
};

class Father:public Human
{
};
class Mother:public Human
{
};

class Son:public Father,public Mother
{
};

int main (void)
{
	Son Tom;
	//Tom.stand();
	//��Ϊ����̳��˸����ĸ������ԣ��������ĸ�඼�̳��������stand���ԣ�ͨ�׵㼴Father����Mother���ж���stand
	//Son��Ķ����ڵ���standʱ����֪���ǵ��ø���̳е�����stand���ԣ�����ĸ��̳е�����stand���ԴӶ�����������
	Tom.Mother::stand();
	Tom.Father::stand();//������������������ɽ��

	return 0;
}
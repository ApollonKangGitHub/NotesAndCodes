# include <iostream>
using namespace std;
class Human
{
public:
	void stand(){cout << "�����ܹ�ֱ������" << endl;}
};

class Father:virtual public Human//�ؼ���virtual˵��Ϊ����࣬stand����ֱ������Father��Ψһֱ��Human
{
};
class Mother:virtual public Human//�ؼ���virtual˵��Ϊ����࣬stand����ֱ������Mother��Ψһֱ��Human
{
};

class Son : public Father, public Mother
{
};

int main (void)
{
	Son Tom;
	Tom.stand();//ֱ�ӵ���Ψһֱ��Human��stand
	Tom.Mother::stand();

	return 0;
}
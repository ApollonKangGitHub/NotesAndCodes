# include <iostream>
using namespace std;

class num
{
public:
	num(){n = 1; cout << "���캯��ִ����..." << endl;}//���캯����ʼ��
	num(int i){n = i; cout << "�������Ĺ��캯��ִ����..." << endl;}
	~num(){cout << "��������ִ����..." << endl;}
	num(const num&s){n = s.n; cout << "���ƹ��캯������ִ����..." << endl;}//this->n = s.n;

	void set(int x){n = x;}
	int get()const{return n;}
	void num_add(){++n;}

	const num & operator++()//ǰ�Լӣ��ȼӺ���
	{
		++n;
		return *this;
	}
	const num operator++(int o)//���Լӣ����ú�ӣ������԰������ͷ��أ���Ϊ��ʱ���󳬳�������ᱻ������
	{
		num TEMP(*this);//��ʱ����,����ԭʼ���󣨵�ǰ����
		++this->n;//ԭʼ�����Աn�Լ�
		return TEMP;//���ص���ʱ������ԭ�ж����Լ�ǰ��ͬ
	}
private:
	int n;
};
int main (void)
{
	num NUM_ONE;
	cout << "NUM_ONE:" << NUM_ONE.get() << endl;

	NUM_ONE.num_add();
	//++NUM_ONE;
	//NUM_ONE++;//���ַ�ʽ�����ͬ���ǻ���ͬ�����ҵ����ֻ��ε��ø��ƹ��캯��

	cout << "NUM_ONE:" << NUM_ONE.get() << endl;
	
	//num NUM_TWO = ++NUM_ONE;
	num NUM_TWO = NUM_ONE++;

	cout << "NUM_TWO:" << NUM_TWO.get() << endl;
	cout << "NUM_ONE:" << NUM_ONE.get() << endl;

	++NUM_ONE;
	cout << "NUM_ONE:" << NUM_ONE.get() << endl;
	cout << "NUM_TWO:" << NUM_TWO.get() << endl;
	return 0;
}
/*
num NUM_TWO = ++NUM_ONE;ǰ�Լ����н����

���캯��ִ����...
NUM_ONE:1
NUM_ONE:2
���ƹ��캯������ִ����...
NUM_TWO:3
NUM_ONE:3
NUM_ONE:4
NUM_TWO:3
��������ִ����...
��������ִ����...
Press any key to continue

num NUM_TWO = NUM_ONE++;���Լ����н����
���캯��ִ����...
NUM_ONE:1
NUM_ONE:2
���ƹ��캯������ִ����...
���ƹ��캯������ִ����...		
��������ִ����...					//��ʱ���󴴽�֮�󳬳�������ֱ�ӱ�����
NUM_TWO:2
NUM_ONE:3
NUM_ONE:4
NUM_TWO:2
��������ִ����...
��������ִ����...
Press any key to continue

*/
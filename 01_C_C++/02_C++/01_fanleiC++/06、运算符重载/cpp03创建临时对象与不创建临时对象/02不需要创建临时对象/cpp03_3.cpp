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
	const num & operator++()//���봴�������򰴱�������
	{
		++n;
		return *this;
	}
private:
	int n;
};
int main (void)
{
	num NUM_ONE;
	cout << "NUM_ONE:" << NUM_ONE.get() << endl;
	//NUM_ONE.num_add();//���ᴴ����ʱ����
	++NUM_ONE;//����thisָ�����ԭ�ж����ԼӺ��ֵ��Ҳ���ᴴ����ʱ����
	cout << "NUM_ONE:" << NUM_ONE.get() << endl;
	
	num NUM_TWO = ++NUM_ONE;//���ڷ���ֵΪconst���Բ���++NUM_ONE֮�����Լӣ���++++NUM_ONE
	cout << "NUM_TWO:" << NUM_TWO.get() << endl;
	cout << "NUM_ONE:" << NUM_ONE.get() << endl;

	++NUM_ONE;
	cout << "NUM_ONE:" << NUM_ONE.get() << endl;
	cout << "NUM_TWO:" << NUM_TWO.get() << endl;
	cout << "��NUM_ONE������ı�NUM_ONE��ֵ��������ı�NUM_TWO��ֵ" << endl;
	++NUM_ONE;
	cout << "NUM_ONE:" << NUM_ONE.get() << endl;
	cout << "NUM_TWO:" << NUM_TWO.get() << endl;
	cout << "��NUM_ONE������ı�NUM_ONE��ֵ��������ı�NUM_TWO��ֵ" << endl;
	++NUM_TWO;
	cout << "NUM_ONE:" << NUM_ONE.get() << endl;
	cout << "NUM_TWO:" << NUM_TWO.get() << endl;
	cout << "��NUM_TWO������ı�NUM_TWO��ֵ��������ı�NUM_ONE��ֵ" << endl;

	return 0;
}
# include <iostream>
using namespace std;

class num
{
public:
	num(){n = 1; cout << "���캯��ִ����..." << endl;}//���캯����ʼ��
	num(int i){n = i; cout << "�������Ĺ��캯��ִ����..." << endl;}//�������Ĺ��캯������������֮���ᱻ��������
	num(const num&s){cout << "���ƹ��캯������ִ����..." << endl;}//this->n = s.n;
	~num(){cout << "��������ִ����..." << endl;}
	int get()const{return n;}
	void set(int x){n = x;}

	//const num equal(const num &r){*n = r.get(); return *this;}//����ֵ���Բ�Ҫ
	operator=(const num&r)
	{
		cout << "operator=�������ڵ���..." << endl;
		n = r.n;
	}
private:
	int n;
};
int main (void)
{
	num one(49);
	num two(100);
	cout << "one:" << one.get() << endl;
	cout << "two:" << two.get() << endl;
	one = two;

	cout << "one:" << one.get() << endl;
	cout << "two:" << two.get() << endl;

	return 0;
}

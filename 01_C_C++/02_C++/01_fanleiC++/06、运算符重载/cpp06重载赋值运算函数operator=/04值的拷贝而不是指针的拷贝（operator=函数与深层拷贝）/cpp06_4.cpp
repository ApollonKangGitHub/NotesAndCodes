# include <iostream>
using namespace std;

class num
{
public:
	num(){n = new int; *n = 1; cout << "���캯��ִ����..." << endl;}//���캯����ʼ��
	num(int i){n = new int; *n = i; cout << "�������Ĺ��캯��ִ����..." << endl;}//�������Ĺ��캯������������֮���ᱻ��������
	num(const num&s){n = new int; *n = s.get(); cout << "���ƹ��캯������ִ����..." << endl;}//this->n = s.n;
	~num(){delete n; n = NULL; cout << "��������ִ����..." << endl;}
	int get()const{return *n;}
	void set(int x){*n = x;}

	operator=(const num&r)
	{
		cout << "operator=�������ڵ���..." << endl;
		*n = r.get();
	}
private:
	int *n;
};
int main (void)
{
	num one(49);
	num two(100);
	cout << "one:" << one.get() << endl;
	cout << "two:" << two.get() << endl;
	num three = one = two;

	cout << "one:" << one.get() << endl;
	cout << "two:" << two.get() << endl;
	cout << "three:" << three.get() << endl;

	return 0;
}

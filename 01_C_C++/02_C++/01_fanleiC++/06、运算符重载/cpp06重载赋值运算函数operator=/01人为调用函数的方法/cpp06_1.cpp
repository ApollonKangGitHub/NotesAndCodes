# include <iostream>
using namespace std;

class num
{
public:
	num(){n = 1; cout << "���캯��ִ����..." << endl;}//���캯����ʼ��
	num(int i){n = i; cout << "�������Ĺ��캯��ִ����..." << endl;}//�������Ĺ��캯������������֮���ᱻ��������
	~num(){cout << "��������ִ����..." << endl;}
	num(const num&s){n = s.n; cout << "���ƹ��캯������ִ����..." << endl;}//this->n = s.n;

	void set(int x){n = x;}
	int get()const{return n;}

	const num equal(const num & r){n = r.get(); return *this;}//����ֵ���Բ�Ҫ
private:
	int n;
};
int main (void)
{
	num one(49);
	num two(100);
	num three;

	cout << "one:" << one.get() << endl;
	cout << "two:" << two.get() << endl;
	three = one.equal(two);//��two����one�����ø��ƹ��캯����one���Ƹ�three
	cout << "one:" << one.get() << endl;
	cout << "two:" << two.get() << endl;
	cout << "three:" << three.get() << endl;
	return 0;
}

/*
	2016��8��20��17:33:07
	������Ŀ�����ԱnΪָ�룬delete one�ض���ʹthree��n��Ϊ��;ָ�������ȫ����
	���Ա��������㸴�� 
*/
# include <iostream>
using namespace std;

class num
{
public:
	num(){n = new int; *n = 1; cout << "���캯��ִ����..." << endl;}//���캯����ʼ��
	num(int i){n = new int; *n = i; cout << "�������Ĺ��캯��ִ����..." << endl;}//�������Ĺ��캯������������֮���ᱻ��������
	num(const num&s){n = new int; *n = s.get(); cout << "���ƹ��캯������ִ����..." << endl;}//this->n = s.n;
	~num(){delete n; n = NULL; cout << "��������ִ����..." << endl;}//��������ʱ�������������󣬶���һ������Ķ��пռ䡣ɾ���κ�һ�����󲻻�Ӱ�������Ķ���
	int get()const{return *n;}
	void set(int x){*n = x;}

	const num equal(const num &r){*n = r.get(); return *this;}//����ֵ���Բ�Ҫ
private:
	int *n;
};
int main (void)
{
	num one(49);
	num two(100);
	cout << "one:" << one.get() << endl;
	cout << "two:" << two.get() << endl;
	num three = one.equal(two);//�мǲ��ɷֿ�д����Ϊ����ֵΪconst num����

	cout << "one:" << one.get() << endl;
	cout << "two:" << two.get() << endl;
	cout << "three:" << three.get() << endl;
	return 0;
}

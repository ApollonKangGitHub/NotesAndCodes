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

	//��this��n��r��n��ӣ���Ϊ���캯��num�Ĳ�����������ӷ���ͬС��
	num num_add(const num&r){return num(n+r.get());}//��Ϊ���е��ú����ķ�����������Ӻ�Ķ���
	const num operator+(const num&r){return num(n+r.get());}//��������صķ�������ϵͳ���е��ú����ķ���
private:
	int n;
};
int main (void)
{
	num one(12), two(20), three;//one�����two�����ʼ��

	//three = one.num_add(two);
	//three = two.num_add(one);//����д����һ����
	three = one + two;//�Զ�����operator+()������һ��������Ϊthisָ����ָ��Ķ�����һ������Ϊoperator+�Ĳ���

	cout << "one:" << one.get() << endl;
	cout << "two:" << two.get() << endl;
	cout << "three:" << three.get() << endl;

	return 0;
}

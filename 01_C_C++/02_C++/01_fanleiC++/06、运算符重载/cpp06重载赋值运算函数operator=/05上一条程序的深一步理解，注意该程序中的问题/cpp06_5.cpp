# include <iostream>
using namespace std;

class num
{
public:
	num(){n = new int; *n = 1; cout << "���캯��ִ����..." << endl;}//���캯����ʼ��
	//num(int i){n = new int; *n = i; cout << "�������Ĺ��캯��ִ����..." << endl;}//�������Ĺ��캯������������֮���ᱻ��������
	//num(const num&s){n = new int; *n = s.get(); cout << "���ƹ��캯������ִ����..." << endl;}//this->n = s.n;
	~num(){delete n; n = NULL; cout << "��������ִ����..." << endl;}
	int get()const{return *n;}
	void set(int x){*n = x;}

	//const num &operator=(const num & r)//�����÷��ز����ø��ƹ��캯��
	num operator=(const num & r)
	{
		if(this == &r)
		{
			return *this;
		}
		cout << "operator=�������ڵ���..." << endl;
		*n = r.get();
		return *this;
	}
private:
	int *n;
};
int main (void)
{
	num one, two;
	one.set(14);
	two.set(27);
	cout << "one:" << one.get() << endl;
	cout << "two:" << two.get() << endl;

	//num three = one = two;
	num three;
	three = one = two;
	//˼��1������͸�ֵΪ����Ͷ��帳ֵΪһ�䣬Ϊʲô���ǳ���������������ͬ�أ�����
	//˼��2���ĳ���Ϊʲô�����Ϊʲô����cpp06_4 ���������
	//˼��3��Ϊʲô�����ƹ��캯����ע�ͷ���//��ȥ��֮������ͽ�����أ�����
	//˼��4��Ϊʲô��ȥ�����ƹ��캯����ע�ͷ���//����
	//����num operator=(const num&r)��Ϊconst num &operator=(const num&r)����Ҳ���Խ���أ���const�޹أ���Ҫ�����õ����ã�����
	cout << "one:" << one.get() << endl;
	cout << "two:" << two.get() << endl;
	cout << "three:" << three.get() << endl;

	return 0;
}

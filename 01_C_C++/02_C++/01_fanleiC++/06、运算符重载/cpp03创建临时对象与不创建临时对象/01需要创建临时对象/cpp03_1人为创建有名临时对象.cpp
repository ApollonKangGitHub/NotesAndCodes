
# include <iostream>
using namespace std;

class num
{
public:
	num(){n = 1; cout << "���캯��ִ����..." << endl;}//���캯����ʼ��
	~num(){cout << "��������ִ����..." << endl;}

	//num(num&){cout << "���ƹ��캯��ִ����..." << endl;}
	/*
		ע�⣺
		���дĬ�ϸ��ƹ��캯����operator+���������ǰ�ֵ���أ�Ϊǳ�㿽����
		��ǳ�㿽������ʱ���������󣬸��Ƶ�ֵ���ڵĿռ䣨������������ĸ����ռ䣩�ᱻ�ͷ�
		���������ֵΪ���ֵ
	*/

	void set(int x){n = x;}
	int get(){return n;}
	void num_add(){++n;}
	num operator++()
	{
		++n;
		num TEMP;//��ʱ����
		TEMP.set(n);
		return TEMP;
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
	cout << "NUM_ONE:" << NUM_ONE.get() << endl;	

	num NUM_TWO = ++NUM_ONE;
	//���void operator++(){++n;}���䡣num NUM_TWO = ++NUM_ONE;��ô����д���Ǵ���ġ�
	//��Ϊ++NUM_ONE����operator++��������ֵΪvoid������NUM_TWO���Ͳ�ƥ��
	//Ҫʵ�ֽ�һ�������ԼӺ󸳸�һ���µĶ��󣬱��봴��һ����ʱ����,�����е�operator++()��д��
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
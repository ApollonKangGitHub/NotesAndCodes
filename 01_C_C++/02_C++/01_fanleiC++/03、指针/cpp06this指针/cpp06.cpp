# include <iostream>
using namespace std;

class Human
{
public:
	int get_i()const{return i;}
	void set_i (int x){i = x;cout << "thisָ�뱣����ڴ��ַΪ��\t" << this << endl;}
//	int get_j()const{return j;}
//	void set_j (int x){j = x;cout << "thisָ�뱣����ڴ��ַΪ��\t" << this << endl;}
private:
	int i;
//	int j;
};
int main (void)
{
	Human a;
	a.set_i(9);
//	a.set_j(90);
	cout << "����a���ڴ��ַΪ��\t\t" << &a << endl;
	cout << a.get_i() <<endl;
//	cout << a.get_j() <<endl;

	Human b;
	b.set_i(99);
//	b.set_j(909);
	cout << "����b���ڴ��ַΪ��\t\t" << &b <<endl;
	cout << b.get_i() <<endl;
//	cout << b.get_j() <<endl;

	cout << sizeof(a) << endl;
	cout << sizeof(b) << endl;
	
	return 0;
}
/*

void set_i (int x){i = x;cout << "thisָ�뱣����ڴ��ַΪ��\t" << this << endl;}
ԭ�����Ϊ:
void set (int x){this->i = x;cout << "thisָ�뱣����ڴ��ַΪ��\t" << this << endl;}
this����ʡ�Բ�л���������Զ������this


this������¼ÿ������ĵ�ַ��Ȼ��ͨ����ӷ��������->�����ʸö���ĳ�Ա
this��¼���Ƕ���ĵ�ַ��ĳ�������ж�������������ַ���ֽڼ����һ�������ĵ�ַ���ֽ���ͬ

*/
# include <iostream>
using namespace std;
class ONE
{
public:
	void hello(){cout << "����ONE��hello����" << endl;}
	void hello(int i)
	{
		cout << "����ONE�Ĵ�����hello����";
		cout << "hello(i):" << i << endl;
	}
	void print(int j)
	{
		cout << "����ONE�Ĵ�����print����";
		cout << "hello(j):" << j << endl;
	}
};

class TWO:public ONE
{
public:
	void hello(){cout << "����TWO��hello����" << endl;}
	void print(){cout << "����TWO��print����" << endl;}

	void print(int j)const//��const�벻��const���麯���е����������ԣ��˴���������
	{
		cout << "����TWO�Ĵ�����print����";
		cout << "hello(j):" << j << endl;
	}

};

int main (void)
{
	ONE Jack;
	TWO Mike;

	Jack.hello();
	Jack.hello(1245);
	Mike.hello();
	//Mike.hello(2);
	//��Ȼ�в������𣬲��ᵼ�º�������ʱ���޷��ֱ棬���Ǻ���Ȼ�������Ϊ�����д����������غ����������ͬ����hello�������ص��ˡ�
	//������hello����û�в�����������ֱ���ҵ�������ƥ��������е�hello������������ȥ������Ѱ�Ҵ�������hello����
	//����������hello������û�в������³��������ԭ���Ǳ�����û���ҵ�����Ҫ�õ�hello��������Ϊ�ҵ��ˣ��������������޷����֣�֪��û�ҵ���
	Mike.ONE::hello(2);//�����������������Ͳ��������

	//�������ԭ�м̳еĻ����еĺ�����������Ҫ���£��ɵģ����ࣩ�����Ѿ�����̭���ڲ���ԭ�л����ǰ���£�ֻ��Ҫ�����������¶��������������
	//�����̳е�һ���ֿ���ֱ��ʹ�ã�һ���ֱ�������µĳ�Ա���ǣ���constΪ��ȫ���ǣ�����constΪ��������
	Mike.print(2451);
	Mike.ONE::print(1457);
	
	return 0;
}
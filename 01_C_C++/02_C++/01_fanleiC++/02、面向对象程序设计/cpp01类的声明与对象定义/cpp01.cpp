# include <iostream>
using namespace std;

/*
***  classΪ��ؼ��֣�������struct
***  publicΪ���г�Ա
***  privateΪ˽�г�Ա
***  ˽�г�Ա����ͨ��������ֱ�ӷ��ʣ�����ͨ�����������ù��г�Ա->���г�Ա����˽�г�Ա��ʵ��
*/
class Human
{
public:
	void get_stature(){cout<<stature<<endl;}//ֱ�Ӷ���
	void get_weight(){cout<<weight<<endl;}
	void set_stature(int x);//�ӿں���
	void set_weight(int x);//�ӿں���
private:
	int weight;
	int stature;
};
/*
***���г�Ա�����Ķ������ֱ�������Ա������ֱ�Ӷ��壬
***Ҳ����������������������ͨ��������ȡ������ȫ�ֶ���
*/
void Human::set_stature(int x)//ͨ��������ȡ��Ա������������
{
	stature = x;
}

void Human::set_weight(int x)
{
	weight = x;
}

int main (void)
{
	Human Mike;
	int weight;
	int stature;

	cout<<"������Mike������أ�\n";
	cin>>stature>>weight;

	cout<<"Mike�����Ϊ��cm����";
	Mike.set_stature(stature);//���������ù��г�Ա���������У�->���г�Ա����˽�г�Ա������������ɣ�
	Mike.get_stature();//������ֱ�ӵ��ù��г�Ա
	cout<<"Mike������Ϊ��kg����";
	Mike.set_weight(weight);
	Mike.get_weight();

	return 0;
}
/*
	����ĳ����������ݺͷ����ļ��ϣ�
	���������ɸ���������غ�������ɣ����������ӵ����Щ����������ͨ�����������壬��ͨ���ؼ���class��������
	��Ĺ�ͬ���ݽ�����Ա���������ݳ�Ա������Ĺ�ͬ����������Ա������������Ա������Ա�����ͳ�Ա����ͳ��Ϊ����ĳ�Ա
	����ӵ����Ĺ��г�Աֱ�ӵ���Ȩ�ޣ����ҿ��Է�װ��Щ��Ա
*/
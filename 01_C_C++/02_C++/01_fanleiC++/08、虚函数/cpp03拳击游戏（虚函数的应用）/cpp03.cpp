/*
ע�⣺
	һ�����еĺ�����˵��Ϊ�麯������������������ͬ�����������˸��麯��
	��ô�������еĸ�ͬ������Ҳ�Ǹ��麯�����������ǿ���ֱ���������������е�ͬ������Ϊ�麯���Եø�����
*/
# include <iostream>
using namespace std;
class poser
{
public:
	virtual void beat()const{cout << "һ��ѡ��һȭ������Ϊ260��\n";}
protected:
	int age;
};
class Ali:public poser
{
	void beat()const{cout << "Aliѡ��һȭ������Ϊ420��\n";}//ҲΪ�麯��
	//virtual void beat()const{cout << "Aliѡ��һȭ������Ϊ420��\n";}����������һ����
};
class Lewis:public poser
{
	void beat()const{cout << "Lewisѡ��һȭ������Ϊ480��\n";}//ҲΪ�麯��
};
class Tyson:public poser
{
	void beat()const{cout << "Tysonѡ��һȭ������Ϊ500��\n";}//ҲΪ�麯��
};
class Holy:public poser
{
	void beat()const{cout << "Holyѡ��һȭ������Ϊ400��\n";}//ҲΪ�麯��
};

int main (void)
{
	poser * p[5];//������ָ�����飬����Ԫ��������������ָ�롣��ָ�����������������ָ��
	poser * pi;
	int choice, i;
	for(i = 0; i < 5; ++i)
	{
		cout << "(1)����  (2)����˹  (3)̩ɭ  (4)�����ƶ���:\n";
		cin >> choice;
		switch(choice)
		{
		case 1:
			pi = new Ali;
			break;
		case 2:
			pi = new Lewis;
			break;
		case 3:
			pi = new Tyson;
			break;
		case 4:
			pi = new Holy;
			break;
		default:
			pi = new poser;
			break;
		}
		p[i] = pi;
		p[i]->beat();//ͨ��ָ�����ָ���ָ���beat()����
		//��ͬ��poser����ͬ�Ķ�����������ͬ�ĺ�������������ͬ��Ч��
	}
	return 0;
}
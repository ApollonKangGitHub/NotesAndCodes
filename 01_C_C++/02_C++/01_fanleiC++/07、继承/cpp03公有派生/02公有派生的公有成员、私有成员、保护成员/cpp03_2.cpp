/*
	2016��8��22��11:22:39
	���н�����Զ����ڹ���������ǰ���¼�class SON:public FATHER
*/
# include <iostream>
using namespace std;

class FATHER
{
protected:		
	void money(){cout << "���׵�Ǯ��" << endl;}//���׵�Ǯ��
public:
	void room(){cout << "���׵ķ���" << endl;}//���׵ķ���
private:
	void secret(){cout << "���׵�����" << endl;}//���׵�����
};

class SON:public FATHER//��������
{
private:

public:
	void mother(){money();}
	//void mother_grand(){secret();}

};

int main (void)
{
	SON Mike;
	cout<<"����Mike�������ã�" << endl;
	Mike.room();
	//Mike.money();
	Mike.mother();//����ı�����Ա��Ǯ�ƣ�������ֱ�ӷ��ʣ�����ͨ�������еĹ��нӿڣ�ĸ�ף�������
	//Mike.mother_grand();//���׵�˽�г�Ա�����ܣ������Ӳ����Է��ʡ���ʹͨ�������еĹ��нӿڣ�ĸ�׻���ĸ�游��Ҳ�����ԡ�
	return 0;
}
# include<iostream>
using namespace std;

class father 
{
public:
	virtual void run()const{cout << "���׿���������" << endl;}
};

class son:public father
{
	virtual void run()const{cout << "���ӿ�����ʮ����" << endl;}
};
class daughter:public father
{
	virtual void run()const{cout << "Ů��������ʮ����" << endl;}
};
void one (father);
void two (father*);
void two (father&);

void one(father one)
{
	one.run();//����ֱ�ӵ���
}
void two (father * two)
{
	two->run();//ָ�����
}
void three (father & three)
{
	three.run();//���õ���
}
int main(void)
{
	father * p = NULL;
	int choice = 0;
	while(1)
	{
		bool quit = false;
		cout << "(0)quit    (1)son    (2)daughter    (3)father    " << endl;
		cin >> choice;
	
		switch(choice)
		{
		case 0:quit = true;
			break;
		case 1:p = new son;
			one(*p);//pΪfather *��ָ�룬*p��Ϊ����̳и�������г�Ա��������ĳ�Ա���Ұ�ֵ���ε����麯��Ϊ��̬����
			break;
		case 2:p = new daughter;
			two(p);//��ָ�봫�Σ������麯�����麯����������ʱ�Ķ�̬����
			break;
		case 3:p = new father;
			three(*p);//�������õķ�ʽ���Σ������麯��
			break;
		default:cout<< "��������Чѡ��0��1��2��3��" << endl;
			break;
		}	
		if(true == quit)	break;
	}
	return 0;
}
/*
	2016��8��22��12:50:56
	���ؼ̳е�ʹ����Ȩ�����ã����ýӿں�����
*/
# include <iostream>
using namespace std;

class Father
{
public:
	void set_F(int a){high = a;}
	void print_F(){cout << "���(CM)=" << high << endl;}
private:
	int high;
};

class Mother
{	
public:
	void set_M(int a){weight = a;}
	void print_M(){cout << "����(KG)=" << weight << endl;}
private:
	int weight;
};

class Son:public Father,public Mother//���ǹ��м̳�
{
private:
	int age;
public:
	void set_S(int a){age = a;}
	void print_S(){print_F(),print_M(),cout<<"����(��)="<< age << endl;}
};

class Daughter:private Father,public Mother//Father��˽�м̳У�Mother�๫�м̳�
{
private:
	int age;
public:
	void set_D(int a){age = a;}
	void print_D(){cout<<"����(��)="<< age << endl;}
	void SET(int f,int m){set_F(f),set_M(m);}//�ӿں���
	void PRINT(){print_F(),print_M(),cout<<"����(��)="<< age << endl;}//�ӿں���
};

int main (void)
{
	Son Mike;
	cout << "Mike:" << endl;
	Mike.set_F(175);
	Mike.set_M(60);
	Mike.set_S(20);
	Mike.print_F();
	Mike.print_M();
	cout << endl;
	Mike.print_S();

	cout << endl << "Jenny:" << endl;
	Daughter Jenny;

//	Jenny.set_F(165);//˽�м̳в����Ե���
	Jenny.set_M(55);//���м̳п��Ե���
//	Jenny.print_F();//˽�м̳в����Ե���
	Jenny.print_M();//���м̳п��Ե���

	cout << endl;
	Jenny.set_D(20);
	Jenny.print_D();
	cout << endl;
	Jenny.SET(165,57);
	Jenny.PRINT();

	return 0;
}
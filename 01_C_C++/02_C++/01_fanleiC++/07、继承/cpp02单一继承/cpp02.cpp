/*2016��8��22��10:41:39*/
# include <iostream>
using namespace std;

class FATHER
{
private:
	int height;//���
	int weight;//����
public:
	void set_height(int father_height){height = father_height;}//�������
	void set_weight(int father_weight){weight = father_weight;}//��������
	void get_heightandweight(){cout<<"���(cm)="<<height<<"\t����(kg)="<<weight<<endl;}//����������
};

class SON : public FATHER//SON����̳�FATHER���ಢ����������
{
private:
	int shoulder_weidth;//���
	int length_arm;//�۳�
public:
	void set_shoulder_weidth(int son_shoulder_weidth){shoulder_weidth = son_shoulder_weidth;}//���ü��
	void set_length_arm(int son_length_arm){length_arm = son_length_arm;}//���ñ۳�
	void get_shouldrandarm(){cout<<"���(cm)="<<shoulder_weidth<<"\t�۳�(cm)="<<length_arm<<endl;}//��������۳�
};

int main (void)
{
	SON Mike;
	FATHER Koaro;

	cout << "����Mike��" << endl;
	Mike.set_height(175);//SON��Ķ�����Ե����丸��ĳ�Ա����
	Mike.set_weight(65);
	Mike.set_length_arm(70);//SON��Ķ�������Լ��ĳ�Ա����
	Mike.set_shoulder_weidth(40);
	Mike.get_heightandweight();
	Mike.get_shouldrandarm();

	cout << endl << "����Koaro��" << endl;
	Koaro.set_height(170);
	Koaro.set_weight(65);
	Koaro.get_heightandweight();
	return 0;
}
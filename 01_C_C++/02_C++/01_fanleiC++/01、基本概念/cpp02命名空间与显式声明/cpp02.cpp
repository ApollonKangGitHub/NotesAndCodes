# include <iostream>
//using namespace std;//�þ佫std�ռ������к������ͷų���
using std::cout;
using std::cin;
using std::endl;
//��������ֻ��cout��sin��endl�ͷų���
namespace kangruojin
{
	float i = 3.8f;//f�ǽ�c++��Ĭ�ϵĸ�������double����ʽ����Ϊfloat��
	float j = 9.6f;//��������f������־���warning C4305: 'initializing' : truncation from 'const double' to 'float'������Ӱ����
	int k = 10;
};

int main (void)
{
	cout << "Hello everyone!,Please input i j k:" <<endl;
	int i, j;
	float k;
	cin >> i >> j >> k;
	cout << "i = " << i << endl << "j = " << j << endl << "k = " << k << endl ;
	cout << "i = " << kangruojin::i << endl << "j = " << kangruojin::j << endl << "k = " << kangruojin::k << endl ;

	return 0;
}